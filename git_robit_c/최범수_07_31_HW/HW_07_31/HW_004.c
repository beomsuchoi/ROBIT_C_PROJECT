#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int count200us = 0;
unsigned int count_second = 0;
unsigned int calTime = 0;
unsigned char led_now = 0;
unsigned int ms = 0;
unsigned char led_state = 0;

ISR(TIMER0_OVF_vect)
{
	count200us++;
	calTime++;
	if(count200us == 250)
	{
		count_second++;
		if(count_second == 20) // 1초마다 LED 이동 및 UART 전송
		{
			switch(led_state)
			{
				case 0:
				led_now = (led_now + 1) % 8; // 1칸 앞으로
				led_state = 1;
				break;
				case 1:
				led_now = (led_now + 1) % 8; // 1칸 앞으로
				led_state = 2;
				break;
				case 2:
				led_now = (led_now - 1 + 8) % 8; // 1칸 뒤로
				led_state = 3;
				break;
				case 3:
				led_now = (led_now + 1) % 8; // 1칸 앞으로
				led_state = 0;
				break;
			}
			
			PORTA = ~(1 << led_now); // 여집합으로 LED 제어
			UART0_transmit(led_now + '0'); // LED 번호 전송
			count_second = 0;
		}
		count200us = 0;
	}
	if(calTime == 5)
	{
		ms++;
		calTime = 0;
	}
	TCNT0 = 156;
}

void UART0_init(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;   // 통신 속도 설정, 9600
	UCSR0A |= _BV(U2X0);   // 2배속
	
	UCSR0C |= 0x06;   // 비동기, 8비트, 패리티 없음, 1비트 정지 모드
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);  // 송수신 기능 및 수신 인터럽트 활성화
}

void UART0_transmit(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));   // 송신 가능 대기
	UDR0 = data;
}

unsigned char rx_buf;
// 수신 인터럽트 서비스 루틴
ISR(USART0_RX_vect)
{
	rx_buf = UDR0;
	if(rx_buf >= '0' && rx_buf <= '7')
	led_now = rx_buf - '0';
}

int main(void)
{
	DDRA = 0xFF;
	
	TCNT0 = 156;
	TCCR0 = 0x03;    // 분주비 32
	TIMSK = 0x01;
	
	SREG = 0x80;
	
	UART0_init();
	
	lcdInit();
	lcdClear();
	
	// 시간 표시
	unsigned int print_s = 0;
	unsigned int print_min = 0;

	PORTA = ~1;
	while(1)
	{

		if(ms > 999)
		{
			print_s++;
			ms = 0;
		}
		
		if(print_s > 59)
		{
			lcdClear();
			print_s = 0;
			print_min++;
		}
		
		lcdNumber(0, 0, print_min);
		lcdString(0, 3, ":");
		lcdNumber(0, 4, print_s);
		lcdString(0, 6, ".");
		lcdNumber(0, 7, ms);
		

	}
}
