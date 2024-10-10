/*
 * GccApplication1.c
 *
 * Created: 2024-07-26 오전 2:26:49
 * Author : chlqj
 */ 
#define F_CPU 16000000

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t led = 0x01; //첫 번째 LED 켜지게

int main(void)
{
	DDRA = 0xFF;  // 포트 A를 출력으로
	DDRD = 0x00;  // 포트 D를 입력으로
	
	PORTA = 0xFF;//(LED 꺼짐)
	PORTD = 0xFF;
	
	//인터럽트
	EIMSK = (1 << INT2) | (1 << INT3);
	//인터럽트
	EICRA = (1 << ISC21) | (0 << ISC20) | (1 << ISC31) | (0 << ISC30);

	sei();
	
	/* Replace with your application code */
	while (1)
	{
		if((PIND & 0x01) == 0 && (PIND & 0x02) == 0)
		{
			PORTA = 0x00; // LED 켜기
		}
		else
		{
			if ((PIND & 0x01) == 0) // 스위치 1이 눌렸는지 확인
		{
			PORTA = 0xF0; // 4~7번 LED 켜기
		}
		else if ((PIND & 0x02) == 0) // 스위치 2가 눌렸는지 확인
		{
			PORTA = 0x0F; // 0~3번 LED 켜기
		}
		else
		{
			PORTA = 0xFF; //(LED 꺼짐)
			_delay_ms(500);
			PORTA = 0x00; // (LED 켜짐)
			_delay_ms(500);
		}
		}
		
	}
	return 0;
}

ISR(INT2_vect)
{
	// INT2 발생 시 LED 좌측 이동
	if (led & 0x80) {
		led = 0x01;
		} else {
		led <<= 1;
	}
	PORTA = ~led;
}

ISR(INT3_vect)
{
	// INT3 발생 시 LED 우측 이동
	if (led & 0x01) {
		led = 0x80;
		} else {
		led >>= 1;
	}
	PORTA = ~led;
}