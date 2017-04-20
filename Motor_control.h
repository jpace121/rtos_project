#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

/* XDC Module Headers */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>

typedef enum Motors_Side {
    LEFT,
    RIGHT
} Motors_Side;

typedef enum Motors_Dir {
    FORWARD,
    REVERSE
} Motors_Dir;

void motors_Config(void);
void motors_Drive(Motors_Side side, Motors_Dir dir, uint8_t duty_factor);


#endif /* MOTOR_CONTROL_H_ */
