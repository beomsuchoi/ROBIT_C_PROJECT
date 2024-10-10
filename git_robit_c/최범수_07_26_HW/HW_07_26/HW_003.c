#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LCD_Text.h"

volatile unsigned int A = 1;
volatile unsigned int B = 1;
volatile char operator = '+';
volatile unsigned char now_operator = 0;

void printLCD() {
	lcdClear();
	char display[16];
	sprintf(display, "A: %d B: %d", A, B);
	lcdString(0, 0, display);
}

void Result()
 {
	char display[16];
	int result = 0;
	switch (operator) {
		case '+': result = A + B; break;
		case '-': result = A - B; break;
		case '*': result = A * B; break;
		case '/': result = A / B; break;
	}
	sprintf(display, "%d %c %d = %d", A, operator, B, result);
	lcdClear();
	lcdString(0, 0, display);
}

int main(void) {
	DDRA = 0xFF;
	DDRD = 0x00;

	PORTA = 0xFF;
	PORTD = 0xFF;

	lcdInit();
	lcdClear();
	
	while (1) {
		_delay_ms(50);
		
		if ((PIND & 0x01) == 0) 
		{
			_delay_ms(50);
			if ((PIND & 0x01) == 0)
			 {
				A++;
				printLCD();
			}
		}
		
		if ((PIND & 0x02) == 0) 
		{
			_delay_ms(50);
			if ((PIND & 0x02) == 0) 
			{
				now_operator = (now_operator + 1) % 4;
				switch (now_operator) {
					case 0: operator = '+'; break;
					case 1: operator = '-'; break;
					case 2: operator = '*'; break;
					case 3: operator = '/'; break;
				}
				printLCD();
				
			}
		}

		if ((PIND & 0x04) == 0) {
			_delay_ms(50);
			if ((PIND & 0x04) == 0)
			 {
				B++;
				printLCD();
				
			}
		}

		if ((PIND & 0x08) == 0) 
		{
			_delay_ms(50);
			if ((PIND & 0x08) == 0) 
			{
				Result();
				
			}
		}
	}
}