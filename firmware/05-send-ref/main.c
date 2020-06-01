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
#include <stdlib.h>
#include <util/delay.h>
#include "uart.h"
#include "softuart.h"


/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5
#define RX          PD2
#define TX          PD3
#define DELAY       200
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
    
    
    //char at_response_ok[3];
    //char rssi[3];
    uint8_t rx_char = 0;
    //int i;


    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    softuart_init();

    sei();

    softuart_flush_input_buffer();
    //uart_puts("Init\n\r");
    

    for(;;) {
        

        //rx_char = uart_getc();    
        //if(rx_char != 'a') continue;  
        do{
            rx_char = softuart_getchar();
        }while(rx_char != 'a');

        softuart_putchar(rx_char); uart_puts("a sent back\n\r");

        rx_char = 0; 

        PORTB = PORTB ^ _BV(LED_GREEN);
    
    }
    return 0;
}

/* Interrupts --------------------------------------------------------*/
