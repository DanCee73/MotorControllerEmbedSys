#ifndef MTRFUNCT_H_
#define MTRFUNCT_H_

// Pin Defines
#define PORT_E GPIO_PORTE_BASE
#define PORT_D GPIO_PORTD_BASE

// Method Prototype
void init_stepper(void);
void step_cw_15(void);
void step_ccw_15(void);
void step_variable_x(uint32_t deg_x);
void step_ccw_once(void);
void step_cw_once(void);

// Data Defines
#define HIGH 0xff
#define LOW 0x00
#endif  /* MTRFUNCT_H_  */
