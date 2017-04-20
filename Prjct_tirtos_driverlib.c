/*
 * Code for Zumo Chassis Robot, programmed for Real Time
 * Operating Systems Spring 2017.
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

/* XDC Module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>

/* BIOS Module Headers */
#include <ti/sysbios/BIOS.h>

/* Example/Board Header files */
#include "Board.h"
#include "Motor_control.h"
#include "Current_log.h"

/* Project submodule header fi les.  */


/*
 *  ======== main ========
 */
int main()
{
    /* Call driver init functions */
    Board_initGeneral();

     // Initialize motors.
    motors_Config();
    // Initialize ADC.
    current_Config();

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    BIOS_start();
    return(0);
}
