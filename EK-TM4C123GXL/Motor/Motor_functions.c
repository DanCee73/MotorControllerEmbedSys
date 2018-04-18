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

struct State{
  unsigned char Out;           // Output
  const struct State *Next[2]; // CW/CCW
};

StateType fsm[4]={
  {10,{&fsm[1],&fsm[3]}},
  { 9,{&fsm[2],&fsm[0]}},
  { 5,{&fsm[3],&fsm[1]}},
  { 6,{&fsm[0],&fsm[2]}}
};
unsigned char Pos;      // between 0 and 199
const struct State *Pt; // Current State

void init_stepper(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);    // Enable port D
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    // Enable Port E
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
    GPIOPinTypeGPIOOutput(PORT_E,  GPIO_PIN_4 | GPIO_PIN_5);    // Set Port E pins 4,5 to outputs
    GPIOPinTypeGPIOOutput(PORT_D,  GPIO_PIN_2 | GPIO_PIN_3);    // Set Port D pins 2,3 to outputs
    Pos = 0;
    Pt = &fsm[0];
}

// call this function to step CW 15 degs
void step_cw_15(void){
    uint8_t x;
    for (x = 0; x<7; x++){
    Pt = Pt->Next[clockwise];     // circular
      STEPPER = Pt->Out; // step motor
      if(Pos==199){      // shaft angle
        Pos = 0;         // reset
      }
      else{
        Pos++; // CW
      }
    }
      delayMs(8);    // time to wait for motor to step once (1ms per step),
                          // so for 15degs/1.8degs = 8.33 steps.
}

// call this function to step CCW 15 degs
void step_ccw_15(void){
    uint8_t x;
    for (x = 0; x<7; x++){
    Pt = Pt->Next[counterclockwise]; // circular
      STEPPER = Pt->Out; // step motor
      if(Pos==0){        // shaft angle
        Pos = 199;       // reset
      }
      else{
        Pos--; // CCW
      }
    }
      delayMs(8);    // time to wait for motor to step once (1ms per step),
                          // so for 15degs/1.8degs = 8.33 steps.
}

//call this function to step CCW one time (1.8 degs)
void step_ccw_once(void){

    Pt = Pt->Next[counterclockwise]; // circular
          STEPPER = Pt->Out; // step motor
          if(Pos==0){        // shaft angle
            Pos = 199;       // reset
          }
          else{
            Pos--; // CCW
          }

          delayMs(1);    // time to wait for motor to step once (1ms per step),
                              // so for 15degs/1.8degs = 8.33 steps.
}

//call this function to step CW one time (1.8 degs)
void step_cw_once(void){
    Pt = Pt->Next[clockwise];     // circular
          STEPPER = Pt->Out; // step motor
          if(Pos==199){      // shaft angle
            Pos = 0;         // reset
          }
          else{
            Pos++; // CW
          }

          delayMs(1);    // time to wait for motor to step once (1ms per step),
                              // so for 15degs/1.8degs = 8.33 steps.
}
// call this function passing in the amount of degrees desired
void step_variable_x(unsigned char deg_x){
    short CWsteps;
    unsigned char pos_x;
    pos_x = deg_x / 1.8;
      if((CWsteps = (pos_x-Pos))<0){
        CWsteps+=200;
      } // CW steps is 0 to 199
      if(CWsteps > 100){
        while(pos_x != Pos){
            step_ccw_once();
        }
      }
      else{
        while(pos_x != Pos){
            step_cw_once();
        }
      }

}
