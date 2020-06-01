/***********************************************************************
 * 
 * Blink a LED with the delay function.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "softuart.h"


/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5
#define RX          PD2
#define TX          PD3
#define BLINK_DELAY 500
#define UART_BAUD_RATE 9600


/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/* Main --------------------------------------------------------------*/




/* Toggle a LED with the delay function. */
int main(void)
{
    DDRB = DDRB | _BV(LED_GREEN);       // DDRB OR 0010 0000
    PORTB = PORTB & ~_BV(LED_GREEN);    // PORTB AND 1101 1111
    
    uint8_t c = 'b';


    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    softuart_init();



    
    sei();
    //uart_puts("UART init\r\n");
    

    

    for (;;) {
        uart_putc(c);
        softuart_putchar(c);
        PORTB = PORTB ^ _BV(LED_GREEN);
        _delay_ms (BLINK_DELAY);
    }    

    return 0;
}

/* Interrupts --------------------------------------------------------*/
