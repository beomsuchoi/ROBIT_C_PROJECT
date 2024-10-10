/*
 * test3.c
 *
 * Created: 2024-07-29 오전 2:46:38
 * Author : chlqj
 */ 

#include <avr/io.h>
#include "LCD_Text.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

int main(void)
{
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	SREG = 0x80;
	
	lcdInit();
	lcdClear();
    /* Replace with your application code */
    while (1) 
    {
		unsigned int adcValue = 0;
		unsigned char channel = 0x00;
		double Voltage;
		
		DDRA = 0xFF;
		DDRD = 0x00;
		
		 PORTA = 0xFF;//(LED 꺼짐)
		PORTD = 0xFF;
		char volt[10];
		ADMUX = 0x40 | channel;
		ADCSRA |= 0x40;
		while((ADCSRA&0x10)==0);
		adcValue = ADC;
		Voltage = adcValue * 5.0 / 1024.0;
		sprintf(volt, "%.5lf",Voltage);
		_delay_ms(100);
		
		
		
		lcdString(0, 0, "19th_CBS");
		lcdNumber(1, 0, adcValue);
		lcdString(1, 9, volt);
		
		// adc 값에 따라 LED 이동
		if (adcValue <= 128) PORTA = 0b11111110;
		else if (128 < adcValue && adcValue <= 256) PORTA = 0b11111101;
		else if (256 < adcValue && adcValue <= 384) PORTA = 0b11111011;
		else if (384 < adcValue && adcValue <= 512) PORTA = 0b11110111;
		else if (512 < adcValue && adcValue <= 640) PORTA = 0b11101111;
		else if (640 < adcValue && adcValue <= 768) PORTA = 0b11011111;
		else if (768 < adcValue && adcValue <= 896) PORTA = 0b10111111;
		else if (896 < adcValue) PORTA = 0b01111111;
		
		_delay_ms(100);
		
		lcdInit();
		lcdClear();
		
    }
}

