#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

unsigned int count8ms = 0;
unsigned int num8ms = 0;
unsigned int ms = 0, sec = 0, min = 0, hour = 0;
unsigned int day = 1, month = 1, year = 2019;
unsigned int adcValue = 0;
unsigned char setting_mode = 0;
unsigned char time_running = 0;

void update_time() {
	if (count8ms >= 1000) {
		count8ms = 0;
		sec++;
		if (sec >= 60) {
			sec = 0;
			min++;
			if (min >= 60) {
				min = 0;
				hour++;
				if (hour >= 24) {
					hour = 0;
					day++;
					if (day > month) {
						day = 1;
						month++;
						if (month > 12) {
							month = 1;
							year++;
						}
					}
				}
			}
		}
	}
}

void display_time() {
	lcdClear();
	
	lcdNumber(0,0, year);
	
	lcdNumber(0, 4, month);
	
	lcdNumber(0, 6, day);
	
	lcdNumber(1, 0, hour);
	lcdString(1, 2, ":");

	lcdNumber(1, 3, min);
	lcdString(1, 5, ":");

	lcdNumber(1, 6, sec);
	lcdString(1, 8, ".");

	lcdNumber(1, 9, count8ms);
}

int main(void) {
	TCNT0 = 156;
	TCCR0 = 0x03;
	TIMSK = 0x01;
	sei();

	// ADC 설정
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;

	lcdInit();
	lcdClear();

	EIMSK |= (1 << INT0) | (1 << INT1);

	EICRA |= (1 << ISC01) | (0 << ISC00) | (1 << ISC11) | (0 << ISC10);

	
	SREG = 0x80;
	
	year = 2024;
	ms = 500;

	while (1) {


		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC));
		adcValue = ADC;
		
		switch (setting_mode) {
			case 0:
			if(adcValue < 500)
			{
				year--;
				_delay_ms(700);
			}
			else if(adcValue > 500)
			{
				year++;
				_delay_ms(700);
			}
			break;
			case 1:
			if (adcValue <= 85) month = 1;
			else if (adcValue <= 171) month = 2;
			else if (adcValue <= 256) month = 3;
			else if (adcValue <= 341) month = 4;
			else if (adcValue <= 427) month = 5;
			else if (adcValue <= 512) month = 6;
			else if (adcValue <= 598) month = 7;
			else if (adcValue <= 683) month = 8;
			else if (adcValue <= 768) month = 9;
			else if (adcValue <= 854) month = 10;
			else if (adcValue <= 939) month = 11;
			else if (adcValue <= 1023) month = 12;
			break;
			case 2:
			if (adcValue <= 33) day = 1;
			else if (adcValue <= 65) day = 2;
			else if (adcValue <= 98) day = 3;
			else if (adcValue <= 131) day = 4;
			else if (adcValue <= 164) day = 5;
			else if (adcValue <= 197) day = 6;
			else if (adcValue <= 230) day = 7;
			else if (adcValue <= 262) day = 8;
			else if (adcValue <= 295) day = 9;
			else if (adcValue <= 328) day = 10;
			else if (adcValue <= 361) day = 11;
			else if (adcValue <= 394) day = 12;
			else if (adcValue <= 427) day = 13;
			else if (adcValue <= 460) day = 14;
			else if (adcValue <= 492) day = 15;
			else if (adcValue <= 525) day = 16;
			else if (adcValue <= 558) day = 17;
			else if (adcValue <= 591) day = 18;
			else if (adcValue <= 624) day = 19;
			else if (adcValue <= 657) day = 20;
			else if (adcValue <= 689) day = 21;
			else if (adcValue <= 722) day = 22;
			else if (adcValue <= 755) day = 23;
			else if (adcValue <= 788) day = 24;
			else if (adcValue <= 821) day = 25;
			else if (adcValue <= 854) day = 26;
			else if (adcValue <= 886) day = 27;
			else if (adcValue <= 919) day = 28;
			else if (adcValue <= 952) day = 29;
			else if (adcValue <= 985) day = 30;
			else if (adcValue > 985) day = 31;
			break;
			case 3:
			if (adcValue <= 42) hour = 0;
			else if (adcValue <= 84) hour = 1;
			else if (adcValue <= 126) hour = 2;
			else if (adcValue <= 168) hour = 3;
			else if (adcValue <= 210) hour = 4;
			else if (adcValue <= 252) hour = 5;
			else if (adcValue <= 294) hour = 6;
			else if (adcValue <= 336) hour = 7;
			else if (adcValue <= 378) hour = 8;
			else if (adcValue <= 420) hour = 9;
			else if (adcValue <= 462) hour = 10;
			else if (adcValue <= 504) hour = 11;
			else if (adcValue <= 546) hour = 12;
			else if (adcValue <= 588) hour = 13;
			else if (adcValue <= 630) hour = 14;
			else if (adcValue <= 672) hour = 15;
			else if (adcValue <= 714) hour = 16;
			else if (adcValue <= 756) hour = 17;
			else if (adcValue <= 798) hour = 18;
			else if (adcValue <= 840) hour = 19;
			else if (adcValue <= 882) hour = 20;
			else if (adcValue <= 924) hour = 21;
			else if (adcValue <= 966) hour = 22;
			else if (adcValue <= 1008) hour = 23;
			else if (adcValue > 1008) hour = 24;
			break;
			case 4:
			if (adcValue <= 16) min = 0;
			else if (adcValue <= 33) min = 1;
			else if (adcValue <= 49) min = 2;
			else if (adcValue <= 66) min = 3;
			else if (adcValue <= 82) min = 4;
			else if (adcValue <= 99) min = 5;
			else if (adcValue <= 115) min = 6;
			else if (adcValue <= 132) min = 7;
			else if (adcValue <= 148) min = 8;
			else if (adcValue <= 165) min = 9;
			else if (adcValue <= 181) min = 10;
			else if (adcValue <= 198) min = 11;
			else if (adcValue <= 214) min = 12;
			else if (adcValue <= 231) min = 13;
			else if (adcValue <= 247) min = 14;
			else if (adcValue <= 264) min = 15;
			else if (adcValue <= 280) min = 16;
			else if (adcValue <= 297) min = 17;
			else if (adcValue <= 313) min = 18;
			else if (adcValue <= 330) min = 19;
			else if (adcValue <= 346) min = 20;
			else if (adcValue <= 363) min = 21;
			else if (adcValue <= 379) min = 22;
			else if (adcValue <= 396) min = 23;
			else if (adcValue <= 412) min = 24;
			else if (adcValue <= 429) min = 25;
			else if (adcValue <= 445) min = 26;
			else if (adcValue <= 462) min = 27;
			else if (adcValue <= 478) min = 28;
			else if (adcValue <= 495) min = 29;
			else if (adcValue <= 511) min = 30;
			else if (adcValue <= 528) min = 31;
			else if (adcValue <= 544) min = 32;
			else if (adcValue <= 561) min = 33;
			else if (adcValue <= 577) min = 34;
			else if (adcValue <= 594) min = 35;
			else if (adcValue <= 610) min = 36;
			else if (adcValue <= 627) min = 37;
			else if (adcValue <= 643) min = 38;
			else if (adcValue <= 660) min = 39;
			else if (adcValue <= 676) min = 40;
			else if (adcValue <= 693) min = 41;
			else if (adcValue <= 709) min = 42;
			else if (adcValue <= 726) min = 43;
			else if (adcValue <= 742) min = 44;
			else if (adcValue <= 759) min = 45;
			else if (adcValue <= 775) min = 46;
			else if (adcValue <= 792) min = 47;
			else if (adcValue <= 808) min = 48;
			else if (adcValue <= 825) min = 49;
			else if (adcValue <= 841) min = 50;
			else if (adcValue <= 858) min = 51;
			else if (adcValue <= 874) min = 52;
			else if (adcValue <= 891) min = 53;
			else if (adcValue <= 907) min = 54;
			else if (adcValue <= 924) min = 55;
			else if (adcValue <= 940) min = 56;
			else if (adcValue <= 957) min = 57;
			else if (adcValue <= 973) min = 58;
			else if (adcValue <= 990) min = 59;
			else if (adcValue > 990) min = 60;
			break;
			case 5: // 초 설정
			if (adcValue <= 16) sec = 0;
			else if (adcValue <= 33) sec = 1;
			else if (adcValue <= 49) sec = 2;
			else if (adcValue <= 66) sec = 3;
			else if (adcValue <= 82) sec = 4;
			else if (adcValue <= 99) sec = 5;
			else if (adcValue <= 115) sec = 6;
			else if (adcValue <= 132) sec = 7;
			else if (adcValue <= 148) sec = 8;
			else if (adcValue <= 165) sec = 9;
			else if (adcValue <= 181) sec = 10;
			else if (adcValue <= 198) sec = 11;
			else if (adcValue <= 214) sec = 12;
			else if (adcValue <= 231) sec = 13;
			else if (adcValue <= 247) sec = 14;
			else if (adcValue <= 264) sec = 15;
			else if (adcValue <= 280) sec = 16;
			else if (adcValue <= 297) sec = 17;
			else if (adcValue <= 313) sec = 18;
			else if (adcValue <= 330) sec = 19;
			else if (adcValue <= 346) sec = 20;
			else if (adcValue <= 363) sec = 21;
			else if (adcValue <= 379) sec = 22;
			else if (adcValue <= 396) sec = 23;
			else if (adcValue <= 412) sec = 24;
			else if (adcValue <= 429) sec = 25;
			else if (adcValue <= 445) sec = 26;
			else if (adcValue <= 462) sec = 27;
			else if (adcValue <= 478) sec = 28;
			else if (adcValue <= 495) sec = 29;
			else if (adcValue <= 511) sec = 30;
			else if (adcValue <= 528) sec = 31;
			else if (adcValue <= 544) sec = 32;
			else if (adcValue <= 561) sec = 33;
			else if (adcValue <= 577) sec = 34;
			else if (adcValue <= 594) sec = 35;
			else if (adcValue <= 610) sec = 36;
			else if (adcValue <= 627) sec = 37;
			else if (adcValue <= 643) sec = 38;
			else if (adcValue <= 660) sec = 39;
			else if (adcValue <= 676) sec = 40;
			else if (adcValue <= 693) sec = 41;
			else if (adcValue <= 709) sec = 42;
			else if (adcValue <= 726) sec = 43;
			else if (adcValue <= 742) sec = 44;
			else if (adcValue <= 759) sec = 45;
			else if (adcValue <= 775) sec = 46;
			else if (adcValue <= 792) sec = 47;
			else if (adcValue <= 808) sec = 48;
			else if (adcValue <= 825) sec = 49;
			else if (adcValue <= 841) sec = 50;
			else if (adcValue <= 858) sec = 51;
			else if (adcValue <= 874) sec = 52;
			else if (adcValue <= 891) sec = 53;
			else if (adcValue <= 907) sec = 54;
			else if (adcValue <= 924) sec = 55;
			else if (adcValue <= 940) sec = 56;
			else if (adcValue <= 957) sec = 57;
			else if (adcValue <= 973) sec = 58;
			else if (adcValue <= 990) sec = 59;
			else if (adcValue > 990) sec = 60;
			break;
		}

		
		display_time();
		
		if(time_running) {
			update_time();
			display_time();
		}
	}

	return 0;
}


ISR(TIMER0_OVF_vect) {
	num8ms++;
	if (num8ms == 5) {
		num8ms = 0;
		count8ms++;
	}
	TCNT0 = 156;
}
ISR(INT0_vect)
{
	setting_mode++;
	_delay_ms(500);
}


ISR(INT1_vect)
{
	time_running = 1;
	count8ms = ms;
	_delay_ms(300);
}
