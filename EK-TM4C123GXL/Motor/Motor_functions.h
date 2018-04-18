#ifndef MTRFUNCT_H_
#define MTRFUNCT_H_

// Pin Defines
#define PORT_E GPIO_PORTE_BASE
#define PORT_D GPIO_PORTD_BASE

// Method Prototype
void init_stepper(void);
void step_cw_15(void);
void step_ccw_15(void);
void step_variable_x(unsigned char pos_x);
void step_ccw_once(void);
void step_cw_once(void);

// Type defines
typedef const struct State StateType;
typedef StateType *StatePtr;

// Data Defines
#define clockwise 0        // Next index
#define counterclockwise 1 // Next index
#define STEPPER  (*((volatile unsigned long *)0x4000703C))
#endif  /* MTRFUNCT_H_  */
