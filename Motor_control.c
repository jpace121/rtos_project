/*
 * Motor_control.c
 *
 * Code that implements the motor control for the Zumo
 * RTOS robot.
 *
 */

#include "Motor_control.h"

#define MAX_DUTY 12000 // 250 Hz (3*10^6/250 = 12000)

// Local variables
uint32_t encoderRight_cnt = 0;
uint32_t encoderLeft_cnt = 0;


static Timer_A_PWMConfig pwmConfigRightA =
{
 TIMER_A_CLOCKSOURCE_SMCLK,
 TIMER_A_CLOCKSOURCE_DIVIDER_1,
 MAX_DUTY,
 TIMER_A_CAPTURECOMPARE_REGISTER_1,
 TIMER_A_OUTPUTMODE_RESET_SET,
 0
};

static Timer_A_PWMConfig pwmConfigRightB =
{
 TIMER_A_CLOCKSOURCE_SMCLK,
 TIMER_A_CLOCKSOURCE_DIVIDER_1,
 MAX_DUTY,
 TIMER_A_CAPTURECOMPARE_REGISTER_2,
 TIMER_A_OUTPUTMODE_RESET_SET,
 0
};

static Timer_A_PWMConfig pwmConfigLeftA =
{
 TIMER_A_CLOCKSOURCE_SMCLK,
 TIMER_A_CLOCKSOURCE_DIVIDER_1,
 MAX_DUTY,
 TIMER_A_CAPTURECOMPARE_REGISTER_3,
 TIMER_A_OUTPUTMODE_RESET_SET,
 0
};

static Timer_A_PWMConfig pwmConfigLeftB =
{
 TIMER_A_CLOCKSOURCE_SMCLK,
 TIMER_A_CLOCKSOURCE_DIVIDER_1,
 MAX_DUTY,
 TIMER_A_CAPTURECOMPARE_REGISTER_4,
 TIMER_A_OUTPUTMODE_RESET_SET,
 0
};

// Functions.

/*
 * Configure the pins needed for motor control.
 */
void motors_Config(void)
{

    // Re-map and configure pins.
    // (Pin mapping contained in "Zumo Robot Pin Assignment" spread sheet.)
    const uint8_t port_mapping[] = {PM_NONE,     // P2_0
                                    PM_NONE,     // P2_1
                                    PM_NONE,     // P2_2
                                    PM_NONE,     // P2_3
                                    PM_TA1CCR1A, // P2_4
                                    PM_TA1CCR2A, // P2_5
                                    PM_TA1CCR3A, // P2_6
                                    PM_TA1CCR4A  // P2_7
    };

    MAP_PMAP_configurePorts((const uint8_t *) port_mapping, PMAP_P2MAP, 1, PMAP_DISABLE_RECONFIGURATION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    // Generate base PWM.
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigRightA);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigRightB);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigLeftA);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigLeftB);

    // Set up interrupts for encoder counts.
    MAP_GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN1);

    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P3, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_LOW_TO_HIGH_TRANSITION);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, GPIO_PIN1);

    MAP_GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN1);

    //MAP_Interrupt_enableInterrupt(INT_PORT3);
    //MAP_Interrupt_enableInterrupt(INT_PORT4);
}

void motor_task(void)
{
    while(1)
     {
         motors_Drive(RIGHT, FORWARD, 100);
         motors_Drive(LEFT, FORWARD, 0);
         Task_sleep(1000);
         motors_Drive(RIGHT, FORWARD, 0);
         motors_Drive(LEFT, FORWARD, 100);
         Task_sleep(1000);
     }
}


/*
 * Set duty cycle of motor for motor on the side designated by motor_side
 * moving in the direction specified buy dir, to the 8-bit value specified
 * by duty_cycle.
 *
 * Ex.
 * motors_Drive(LEFT, FORWARD, 128);
 *
 */
void motors_Drive(Motors_Side side, Motors_Dir dir, uint8_t duty_cycle)
{
    if(side == LEFT && dir == FORWARD)
    {
        pwmConfigLeftA.dutyCycle = duty_cycle*(MAX_DUTY/255);
        pwmConfigLeftB.dutyCycle = 0;
    }
    else if(side == LEFT && dir == REVERSE)
    {
        pwmConfigLeftA.dutyCycle = 0;
        pwmConfigLeftB.dutyCycle = duty_cycle*(MAX_DUTY/255);
    }
    else if(side == RIGHT && dir == FORWARD)
    {
        pwmConfigRightA.dutyCycle = duty_cycle*(MAX_DUTY/255);
        pwmConfigRightB.dutyCycle = 0;
    }
    else if(side == RIGHT && dir == REVERSE)
    {
        pwmConfigRightA.dutyCycle = 0;
        pwmConfigRightB.dutyCycle = duty_cycle*(MAX_DUTY/255);
    }

    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigRightA);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigRightB);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigLeftA);
    MAP_Timer_A_generatePWM(TIMER_A1_BASE, &pwmConfigLeftB);
}

/*
 * Interrupt handlers for the encoder lines to allow for software decoding.
 *
 * Quadrature decoder logic stolen from:
 * http://www.edn.com/design/integrated-circuit-design/4363949/Decode-a-quadrature-encoder-in-software
 * which removes the need to track state.
 *
 * P3.5 -> Right A
 * P3.6 -> Right B
 * P3.7 -> Left A
 * P4.1 -> Left B
 *
 * Because of the wiring, encoder count order does not match with
 * the comments. Works in order implemented here, such that positive
 * encoder count is go forward.
 */
void PORT3Handler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P3);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, status);

    switch(status)
    {
    case GPIO_PIN5: // right A
        // A is high, if here, if B low than A leading
        // if A leading -> positive count else negative count
        if(MAP_GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN6) == 0)
        {
            encoderRight_cnt++;
        }
        else
        {
            encoderRight_cnt--;
        }
        break;
    case GPIO_PIN6: // right B
        // B is high. If A low, B is leading.
        // if A leading -> positive count else negative count
        if(MAP_GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5) == 0)
        {
            encoderRight_cnt--;
        }
        else
        {
            encoderRight_cnt++;
        }
        break;
    case GPIO_PIN7: // left A
        // A is high, if here, if B low than A leading
        // if A leading -> positive count else negative count
        if(MAP_GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1) == 0)
        {
            encoderLeft_cnt--;
        }
        else
        {
            encoderLeft_cnt++;
        }
        break;
    }
}

/*
 * Ditto PORT3_IRQHandler
 */
void PORT4Handler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, status);

    switch(status)
    {
    case GPIO_PIN1: // left B
        // B is high. If A low, B is leading.
        // if A leading -> positive count else negative count
        if(MAP_GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 0)
        {
            encoderLeft_cnt++;
        }
        else
        {
            encoderLeft_cnt--;
        }
        break;
    }
}
