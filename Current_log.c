/*
 * Current_Log.c
 *
 *  Created on: Apr 18, 2017
 *      Author: James
 */

#include "Current_log.h"

#define VOLTAGE_REFERENCE (3.3f)

uint16_t resultsBuffer[2];
float resultsBufferConv[2];

static float ADC_Convert(uint16_t rawADCValue);

/*
 * ADC Functions are not using MAP_* version.
 *
 * For some reason, can't read second channel of ADC when using MAP_ version of libraries.
 * Problem goes away when not using MAP version, so I'm not.
 *
 * Yes, this is stupid...
 *
 * Pins:
 * P5.6 -> Vref+
 * P5.7 -> Vref-
 * P5.4 -> Current L A1
 * P5.5 -> Current R A0
 *
 */

/*
 * Configure the ADC to measure the current.
 */
void current_Config(void)
{
    /* Initializing ADC */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    /* Configuring GPIOs for Analog In */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN5 | GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    /* Set up pins for external voltage reference */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN6 | GPIO_PIN7, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Configure ADC memory with external reference. */
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, false);
    ADC14_configureConversionMemory(ADC_MEM0,
             ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG,
             ADC_INPUT_A0, false); // P5.5
    ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG,
            ADC_INPUT_A1, false); // P5.4

    /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
      *  is complete and enabling conversions */
     ADC14_enableInterrupt(ADC_INT1); //INT1 -> MEM1

     /* Enabling Interrupts */
     //MAP_Interrupt_enableInterrupt(INT_ADC14);

     /* Setting up the sample timer to automatically step through the sequence
      * convert.
      */
     ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

     /* Triggering the start of the sample */
     ADC14_enableConversion();
     ADC14_toggleConversionTrigger();
}

/*
 * Run at end of ADC Conversion.
 */
void ADCHandler(void)
{
    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if(status & ADC_INT1)
    {
        ADC14_getMultiSequenceResult(resultsBuffer);
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

        Semaphore_post(ADC_sem);
    }
}

void ADC_Task(void)
{
    int i;

    while(1)
    {
        Semaphore_pend(ADC_sem, BIOS_WAIT_FOREVER);
        for(i = 0; i < 2; i++)
        {
            resultsBufferConv[i] = ADC_Convert(resultsBuffer[i]);
        }
        Task_sleep(100);
        ADC14_toggleConversionTrigger();
    }
}

static float ADC_Convert(uint16_t rawADCValue)
{
    float voltage;
    voltage = ((float)rawADCValue/16384)*VOLTAGE_REFERENCE;
    // 2^14 -> 16384

    return 36.7f*(voltage/VOLTAGE_REFERENCE) - 18.3f;
    //return voltage;
}

