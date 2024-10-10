#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

unsigned int count8ms = 0;
unsigned int count_cnt = 0;

int main(void)
{
    DDRA = 0xff;
   
   TCNT0 = 156;
   TCCR0 = 0x02;
   TIMSK = 0x01;
   
   SREG = 0x80;
   
   DDRF = 0x00;
   ADMUX = 0x40;
   ADCSRA = 0x87;
   
    lcdInit();
	lcdClear();
	
   unsigned int adcValue = 0;
   unsigned char channel = 0x00;
   
    while (1) 
    {
		
		ADMUX = 0x40 | channel;
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) == 0);
		adcValue = ADC;

		if(adcValue <= 60)count_cnt = 700;
		else if(adcValue <= 120)count_cnt = 800;
		else if(adcValue <= 180)count_cnt = 900;
		else if(adcValue <= 240)count_cnt = 1000;
		else if(adcValue <= 300)count_cnt = 1100;
		else if(adcValue <= 360)count_cnt = 1200;
		else if(adcValue <= 420)count_cnt = 1300;
		else if(adcValue <= 480)count_cnt = 1400;
		else if(adcValue <= 540)count_cnt = 1500;
		else if(adcValue <= 600)count_cnt = 1600;
		else if(adcValue <= 660)count_cnt = 1700;
		else if(adcValue <= 720)count_cnt = 1800;
		else if(adcValue <= 780)count_cnt = 1900;
		else if(adcValue <= 840)count_cnt = 2000;
		else if(adcValue <= 900)count_cnt = 2100;
		else if(adcValue <= 960)count_cnt = 2200;
		else if(adcValue > 960)count_cnt = 2300;
		
		
		lcdNumber(0, 0, adcValue);
		lcdNumber(1, 0, count_cnt);
		
		
		_delay_ms(100);
		lcdClear();
    }
}

ISR(TIMER0_OVF_vect) {
   count8ms++;
   if (count8ms == (count_cnt/50))
   {
      if (PINA == 0xff) PORTA = 0x00;
	  
      else if (PINA == 0x00) PORTA = 0xff;
      count8ms = 0;
   }
   TCNT0 = 156;
}

