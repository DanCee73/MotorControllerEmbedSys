#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"

#include"driverlib/sysctl.h"
#include"driverlib/pin_map.h"
#include"driverlib/gpio.h"
#include"driverlib/pwm.h"
#include "driverlib/sysctl.h"

#include "delay.h"
#include "Motor_functions.h"


void init_stepper(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    // Enable port D
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    // Enable Port E
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    GPIOPinTypeGPIOOutput(PORT_E,  GPIO_PIN_4 | GPIO_PIN_5);    // Set Port E pins 4,5 to outputs
    GPIOPinTypeGPIOOutput(PORT_D,  GPIO_PIN_2 | GPIO_PIN_3);    // Set Port D pins 2,3 to outputs
    GPIOPadConfigSet(PORT_D, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(PORT_E, GPIO_PIN_4 | GPIO_PIN_5, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

}

// call this function to step CW 15 degs
void step_cw_15(void){
    uint8_t x;
    for (x = 0; x<7; x++){
        GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
    }

}

// call this function to step CCW 15 degs
void step_ccw_15(void){
    uint8_t x;
    for (x = 0; x<7; x++){
    GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
    GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
    GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
    GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
    delayMs(1);
    GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
    GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
    GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
    GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
    delayMs(1);
    GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
    GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
    GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
    GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
    delayMs(1);
    GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
    GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
    GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
    GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
    }
}

//call this function to step CCW one time (1.8 degs)
void step_ccw_once(void){

    GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
        delayMs(1);
        GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
        GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
        GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
        GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
}

//call this function to step CW one time (1.8 degs)
void step_cw_once(void){
    GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
            GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
            GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
            GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
            delayMs(1);
            GPIOPinWrite(PORT_D, GPIO_PIN_3, HIGH);
            GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
            GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
            GPIOPinWrite(PORT_E, GPIO_PIN_4, LOW);
            delayMs(1);
            GPIOPinWrite(PORT_D, GPIO_PIN_2, HIGH);
            GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
            GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
            GPIOPinWrite(PORT_E, GPIO_PIN_5, LOW);
            delayMs(1);
            GPIOPinWrite(PORT_E, GPIO_PIN_4, HIGH);
            GPIOPinWrite(PORT_E, GPIO_PIN_5, HIGH);
            GPIOPinWrite(PORT_D, GPIO_PIN_2, LOW);
            GPIOPinWrite(PORT_D, GPIO_PIN_3, LOW);
}
// call this function passing in the amount of degrees desired
void step_variable_x(uint32_t deg_x){
    unsigned char pos_x;
    pos_x = deg_x / 1.8;


}
