/*
 * 07_29_HW.c
 *
 * Created: 2024-07-29 ¿ÀÈÄ 4:41:02
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
volatile unsigned char dynamixelSpeed;
volatile unsigned char dynamixelPosition;
ISR(USART0_RX_vect)
{
    unsigned char receivedValue = UDR0;
    if (receivedValue >= 48 && receivedValue <= 57) {
        num_LCD = receivedValue - 48;
        dynamixelSpeed = num_LCD * 30;
    }
}

void uart_init()
{
   UBRR0L = 1;
   UBRR0H = 0;
   UCSR0A = 0x20;
   UCSR0C = 0x06;
   UCSR0B = 0x18;
      
   UCSR0B |= _BV(RXCIE0);
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

void Driving_MX(unsigned int id, unsigned int position, unsigned int spd)
{
   unsigned char i;
   unsigned char Pos_L, Pos_H, Spd_L, Spd_H;
   unsigned char tx_Buf[20];
   
   Pos_L = position & 0xFF;
   Pos_H = (position >> 8) & 0xFF;
   Spd_L = spd & 0xFF;
   Spd_H = (spd >> 8) & 0xFF;
   
   tx_Buf[0] = 0xFF;
   tx_Buf[1] = 0xFF;
   tx_Buf[2] = id;
   tx_Buf[3] = 7;  // Length = Number of parameters (4) + 2 (ID and length) + 1 (instruction)
   tx_Buf[4] = 0x03;
   tx_Buf[5] = 0x1E;
   tx_Buf[6] = Pos_L;
   tx_Buf[7] = Pos_H;
   tx_Buf[8] = Spd_L;
   tx_Buf[9] = Spd_H;
   
   tx_Buf[10] = 0;
   for(i=2;i<10;i++)
   {
      tx_Buf[10] += tx_Buf[i];
   }
   tx_Buf[10] = ~tx_Buf[10];
   
   for (i = 0; i < 11; i++)
   {
      uart_send(tx_Buf[i]);
      _delay_ms(1);
   }
}


int main(void)
{
    uart_init();
    DDRE = 0x02;
   
   
    DDRF = 0x00;
    ADMUX = 0x40;
    ADCSRA = 0x87;
   
    sei();
    
    lcdInit();
    lcdClear();

    while (1) 
    {
        unsigned int adcValue = 0;
        unsigned char channel = 0x00;
      
        DDRA = 0xFF;
        DDRD = 0x00;
      
        PORTA = 0xFF;
        PORTD = 0xFF;
        ADMUX = 0x40 | channel;
        ADCSRA |= 0x40;
        while((ADCSRA & 0x10) == 0);
        adcValue = ADC;
        

        lcdClear();
        lcdString(0, 0, "Speed: ");
      
        //char buffer[10];
        //snprintf(buffer, sizeof(buffer), "%u", dynamixelSpeed);
        lcdNumber(0, 11, dynamixelSpeed);

        lcdString(1, 0, "Position: ");
        //snprintf(buffer, sizeof(buffer), "%u", adcValue);
        lcdNumber(1, 11, adcValue);
      
        _delay_ms(100);
      
      Driving_MX(1, adcValue, dynamixelSpeed);
      _delay_ms(1500);
    }
}