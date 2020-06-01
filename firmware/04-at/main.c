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
    
    
    char at_response_ok[3];
    uint8_t znak = 'a';
    //char rssi[3];
    int i;


    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    softuart_init();
    
    
    sei();

    softuart_flush_input_buffer();
    uart_puts("Init\n\r");
    

    for(;;) {
        
        
        
        while(!softuart_kbhit());
        
        znak = softuart_getchar();
        
        //do{
        //znak = softuart_getchar();
        //}while(znak != 'a');
        
        if(znak != 'a') continue; //skoci na zacatek for pokud neni 'a'
        znak = 0;


        //Vstup do AT modu
        
        softuart_flush_input_buffer();
        softuart_puts("+++"); //uart_puts("+++");
        _delay_ms (50);
        for (i = 0; i < 3;i++){
            at_response_ok[i] = softuart_getchar();
        }
        at_response_ok[2] = '\0';
        
        //uart_puts(at_response_ok); uart_puts("\n\r");
        
        //AT pro RSSI
        
        softuart_flush_input_buffer();
        softuart_puts("ATDB"); softuart_putchar(0x0D); //uart_puts("ATDB"); 
        _delay_ms (50);
        for (i = 0; i < 3;i++){
            at_response_ok[i] = softuart_getchar();
        }
        at_response_ok[2] = '\0';
        uart_puts(at_response_ok); uart_puts("   ");

        //konec AT

        softuart_puts("ATCN"); softuart_putchar(0x0D); //uart_puts("ATCN"); 
        _delay_ms (50);
        for (i = 0; i < 3;i++){
            at_response_ok[i] = softuart_getchar();
        }
        at_response_ok[2] = '\0';
        //uart_puts(at_response_ok); uart_puts("\n\r");
        
        
        PORTB = PORTB ^ _BV(LED_GREEN);
        softuart_flush_input_buffer();
        _delay_ms(1500);//




    
    }
    
    
    
    return 0;
}

/* Interrupts --------------------------------------------------------*/
