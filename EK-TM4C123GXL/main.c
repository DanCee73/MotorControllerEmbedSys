#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "lcd/lcd_functions.h"
#include "i2c/i2c_setup.h"
#include "delay.h"
#include "keypad/keypad.h"

/*
 * Prototypes
 */

void disp_main_menu();

int main(void)
{

    init_i2c0();
    setup_lcd();
    backlight_on();
    clear_screen();
    cursor_home();
    init_keypad();


    while(1)
    {
        disp_main_menu();
    }

    return 0;
}

void disp_main_menu()
{
    clear_screen();
    print_string_justify("Solar Controller", 1, 0);
    print_string_justify("Please type passwd", 1, 1);
    print_string_justify("Push # to start...", 0, 3);
    cursor_off();
    while(get_input() != '#') {} //loop while waiting for "escape" key
    clear_line(3);
    print_string_justify("Loading menu...", 0, 3);
    delayMs(1000*5);

}

