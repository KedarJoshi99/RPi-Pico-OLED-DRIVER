
#include "pico.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include "../include/picoOled.h"
#include "../include/image.h"

#define PICO_LED 25
#define DEBUG_TRIG 22

#define UINP0 10
#define UINP1 7
#define UINP2 6


t_OledParams g_myOled;

void pinConfig(void){

    // initialise GPIO (Green LED connected to pin 25)
    gpio_init(PICO_LED);
    gpio_set_dir(PICO_LED, GPIO_OUT);

    gpio_init(DEBUG_TRIG);
    gpio_set_dir(DEBUG_TRIG, GPIO_OUT);
    gpio_put(DEBUG_TRIG, 0);

    gpio_init(UINP0);
    gpio_set_dir(UINP0, GPIO_IN);

    gpio_init(UINP1);
    gpio_set_dir(UINP1, GPIO_IN);

    gpio_init(UINP2);
    gpio_set_dir(UINP2, GPIO_IN);


}

// this waits for a user switch
void waitUinp1(void){
uint8_t inpState = 1;

    while (1){
        inpState = gpio_get(UINP1);
        if (inpState == 0) return;
    }
}



int main(){

char msg[] = "\n\n\nHello, world!";


//Initialise I/O
    stdio_init_all(); 
// configure my pins
    pinConfig();
// turn off the LED
    gpio_put(PICO_LED, 0);


// wait for the user to press the user key
//  remove this if there is no key to press
    waitUinp1();

// turn on the user LED
    gpio_put(PICO_LED, 1);

// print a sign-on message to the USB serial
    printf("Hello\n");

// configure the OLED module
    configOled(&g_myOled, i2c0, 0x3c, 0, 1, CTRL_SH1106, H_64, W_132);

// set for TTY mode and print a string
    oledSetTTYMode(&g_myOled, true);
    oledWriteStr(&g_myOled, (const uint8_t *)msg, strlen(msg));

// test line drawing
    oledDraw_line(&g_myOled, 0, 0, 127, 63, WHITE);
    oledDisplay(&g_myOled);

// load and display an image.
    oledBmp_show_image(&g_myOled, image_data, image_size);
// this function must be called after loading the image into
//  the Pi's buffer memory
    oledDisplay(&g_myOled);

// spin here until the heat death of the cosmos, we are reset,
//  or power is removed.
    while (true){}

}