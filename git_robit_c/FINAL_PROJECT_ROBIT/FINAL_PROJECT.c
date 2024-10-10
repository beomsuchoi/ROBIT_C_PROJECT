#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD_Text.h"

int adc_num[10];
unsigned long tare_offset = 0;

volatile uint16_t capture_value = 0;
volatile uint8_t rising_edge = 1;


unsigned int read_adc_value(unsigned int channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // ADC 채널 설정
	ADCSRA |= (1 << ADSC); // 변환 시작
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

void motor_set()
{
	DDRB = 0x6F;
	TCCR1A = 0xA2;
	TCCR1B = 0x1A;
	TCCR1C = 0x00;
	
	ICR1 = 399;
	TCNT1 = 0x00;
	
	SREG = 0x80;
}

void adc_set()
{
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	SREG = 0x80;
}

void weight_init()
{
	DDRA &= ~(1 << PA1);  // PD6 (DT) 입력으로 설정
	DDRA |= (1 << PA3);   // PD7 (SCK) 출력으로 설정
}

unsigned long weight_read()
{
	unsigned long count = 0;

	PORTA &= ~(1 << PA3);  // PD7 (SCK) 낮춤

	// DT 핀이 Low가 될 때까지 대기 (데이터 준비)
	while (PINA & (1 << PA1));

	for (int i = 0; i < 24; i++)
	{
		PORTA |= (1 << PA3);   // PD7 (SCK) 상승 에지
		_delay_us(1);

		count = count << 1;    // 비트를 좌측으로 이동

		if (PINA & (1 << PA1)) // 만약 DT 핀이 High이면
		count++;

		PORTA &= ~(1 << PA3);  // PD7 (SCK) 하강 에지
		_delay_us(1);
	}

	// 추가 클럭 펄스 (25번째) - 게인 설정 (128)
	PORTA |= (1 << PA3);
	_delay_us(1);
	PORTA &= ~(1 << PA3);
	_delay_us(1);

	// 24비트 2의 보수 처리
	if (count & 0x800000)  // 24비트의 최상위 비트가 1이면 음수임
	count |= 0xFF000000; // 부호 확장

	return (unsigned long)count;
}

ISR(TIMER3_CAPT_vect)
{
	if (rising_edge) {
		TCNT3 = 0;  // 타이머 카운터 리셋
		TCCR3B &= ~(1 << ICES3);  // 하강 에지에서 캡처하도록 설정
		rising_edge = 0;
	}
	else {
		capture_value = ICR3;
		TCCR3B |= (1 << ICES3);  // 다시 상승 에지에서 캡처하도록 설정
		rising_edge = 1;
	}
}

void timer3_init()
{
	// 입력 캡처 핀 설정 (PD4/ICP1 핀 입력 모드)
	DDRE &= ~(1 << PE7);

	TCCR3A = 0;

	TCCR3B |= (1 << ICES3);  // 상승 에지에서 캡처
	TCCR3B |= (1 << ICNC3);  // 노이즈 캔슬러 활성화
	TCCR3B |= (1 << CS31);   // 프리스케일러를 8로 설정 (타이머 시작)

	ETIMSK |= (1 << TICIE3);  // 입력 캡처 인터럽트 활성화

	sei();  // 전역 인터럽트 활성화
}

// RGB 값을 읽는 함수
void read_rgb(unsigned int *r, unsigned int *g, unsigned int *b) {
	// RED 필터 선택 (S2 LOW, S3 LOW)
	PORTF &= ~(1 << PF2);
	PORTF &= ~(1 << PF3);
	_delay_ms(100);
	*r = capture_value;

	// GREEN 필터 선택 (S2 HIGH, S3 HIGH)
	PORTF |= (1 << PF2);
	PORTF |= (1 << PF3);
	_delay_ms(100);
	*g = capture_value;

	// BLUE 필터 선택 (S2 LOW, S3 HIGH)
	PORTF &= ~(1 << PF2);
	PORTF |= (1 << PF3);
	_delay_ms(100);
	*b = capture_value;
}

void tcs3200_init() {
	// S0, S1, S2, S3 및 OUT 핀 설정
	DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD5); // S0, S1, LED 출력
	DDRF |= (1 << PF2) | (1 << PF3);  // S2, S3 출력
	
	// 주파수 스케일링 설정 (S0 = HIGH, S1 = LOW)
	PORTD |= (1 << PD2);
	PORTD &= ~(1 << PD3);
	
	// LED 제어
	PORTD |= (1 << PD5); // LED ON
}

int main(void)
{
	adc_set();
	motor_set();
	weight_init();
	lcdInit();
	tcs3200_init();
	timer3_init();

	int weight_cap = 0;
	int red_cap = 0;
	int green_cap = 0;
	int blue_cap = 0;
	int accer_cap = 0;
	int ir_cap = 0;
	while (1)
	{
		
		lcdClear();
		unsigned long weight = weight_read();
		
		for (int i = 0; i < 8; i++)
		{
			unsigned int adc_value = read_adc_value(i);
			adc_num[i] = adc_value;
		}
		
		unsigned int r, g, b;
		read_rgb(&r, &g, &b);
		
		if(adc_num[1] < 100 && ir_cap == 0)
		ir_cap = 1;
		
		else if(ir_cap == 1 && accer_cap != 1)
		{
			if(adc_num[0] < 300)
			{
				red_cap = r;
				green_cap = g;
				blue_cap = b;
				lcdString(0, 0, "CHECK");
				_delay_ms(5000);
			}
			else if(adc_num[0] > 300)
			{
				if(red_cap < 180)
				{
					lcdString(0, 0, "RED");
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(100);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(130);
					if(adc_num[4] < 480)
					accer_cap = 1;
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(120);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(100);
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(100);
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					ir_cap = 0;
				}
				else if(green_cap < 220)
				{
					lcdString(0, 0, "GREEN");
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(100);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(130);
					if(adc_num[4] < 480)
					accer_cap = 1;
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(120);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(100);
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(100);
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					ir_cap = 0;
				}
				else if(blue_cap < 180)
				{
					lcdString(0, 0, "BLUE");
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(500);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(130);
					if(adc_num[4] < 480)
					accer_cap = 1;
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(120);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0.75;
					OCR1B = ICR1 * 0;
					_delay_ms(300);
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					ir_cap = 0;
				}
				else if(weight < 20000)
				{
					lcdString(0, 0, "WEIGHT");
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(130);
					if(adc_num[4] < 480)
					accer_cap = 1;
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(2000);
					PORTB = (PORTB & 0xF0) | 0x05;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0.9;//무한궤도
					_delay_ms(110);
					PORTB = (PORTB & 0xF0) | 0x0A;
					OCR1A = ICR1 * 0;
					OCR1B = ICR1 * 0;//무한궤도
					_delay_ms(3000);
				}
			}
		}
		accer_cap = 0;
		_delay_ms(100);
	}
}