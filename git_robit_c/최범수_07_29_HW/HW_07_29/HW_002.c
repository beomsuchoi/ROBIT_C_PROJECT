/*
 * 07_29_HW.c
 *
 * Created: 2024-07-29 오후 4:41:02
 * Author : chlqj
 */ 
#define F_CPU 16000000
#define _BV(bit)(1<<(bit))

#include <avr/io.h>
#include "LCD_Text.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile unsigned char num_LCD;

ISR(USART0_RX_vect)
{
   num_LCD = UDR0;
}

int main(void)
{
   UBRR0L = 16; UBRR0H = 0;
   UCSR0A = 0x20;
   UCSR0B = 0x98;
   UCSR0C = 0x06;
   
   DDRF = 0x00;
   ADMUX = 0x40;
   ADCSRA = 0x87;
   
   sei();
   

   while (1) 
   {
	   lcdInit();
	   lcdClear();
	   
	   
      unsigned int adcValue = 0;
      unsigned char channel = 0x00;
      
      DDRA = 0xFF;
      DDRD = 0x00;
      
      PORTA = 0xFF; // (LED off)
      PORTD = 0xFF;
      ADMUX = 0x40 | channel;
      ADCSRA |= 0x40;
	  
      while((ADCSRA & 0x10) == 0);
      adcValue = ADC;
      
      lcdString(0,0,"ADC Value ");
     lcdString(1,0,"LED Value ");
	 
     if (adcValue <= 128)
     {
        lcdString(0, 11, "A");
     }
     else if (128 < adcValue && adcValue <= 256)
     {
        lcdString(0, 11, "B");
     }
     else if (256 < adcValue && adcValue <= 384)
     {
        lcdString(0, 11, "C");
     }
     else if (384 < adcValue && adcValue <= 512)
     {
        lcdString(0, 11, "D");
     }
     else if (512 < adcValue && adcValue <= 640)
     {
        lcdString(0, 11, "E");
     }
     else if (640 < adcValue && adcValue <= 768)
     {
        lcdString(0, 11, "F");
     }
     else if (768 < adcValue && adcValue <= 896)-
     {
        lcdString(0, 11, "G");
     }
     else if (896 < adcValue)
     {
        lcdString(0, 11, "H");
     }
	 
      char buffer[10];
      snprintf(buffer, sizeof(buffer), "%u", adcValue);
      uart_send_string(buffer);
      uart_send('\n');
      
     
      
     
     
        if (num_LCD == 48)
        {
           PORTA = 0b11111110;
           lcdNumber(1, 11, 0);
        }
        else if (num_LCD == 49)
        {
           PORTA = 0b11111101;
           lcdNumber(1, 11, 1);
        }
        else if (num_LCD == 50)
        {
           PORTA = 0b11111011;
           lcdNumber(1, 11, 2);
        }
        else if (num_LCD == 51)
        {
           PORTA = 0b11110111;
           lcdNumber(1, 11, 3);
        }
        else if (num_LCD == 52)
        {
           PORTA = 0b11101111;
           lcdNumber(1, 11, 4);
        }
        else if (num_LCD == 53)
        {
           PORTA = 0b11011111;
           lcdNumber(1, 11, 5);
        }
        else if (num_LCD == 54)
        {
           PORTA = 0b10111111;
           lcdNumber(1, 11, 6);
        }
        else if (num_LCD == 55)
        {
           PORTA = 0b01111111;
           lcdNumber(1, 11, 7);
        }
		_delay_ms(100);
    }
}

void uart_init(unsigned int ubrr)
{
    UCSR0A |= _BV(U2X0);

    UBRR0H = 0x00;
    UBRR0L = 0x16;

    UCSR0C |= 0x06;

    UCSR0B |= _BV(RXEN0);
    UCSR0B |= _BV(TXEN0);
}

void uart_send(unsigned char data_send)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data_send;
}

void uart_send_string(const char *str)
{
   while (*str)
   {
      uart_send(*str++);
   }
}