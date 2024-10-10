#define F_CPU 16000000
#define _BV(bit)(1<<(bit))

#include <avr/io.h>
#include "LCD_Text.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile unsigned char num_LCD;
volatile unsigned char num_print;
volatile unsigned char led_state = 0xFF;

ISR(USART0_RX_vect) {
	num_LCD = UDR0;
	num_print = num_LCD;
}

int x = 0;
void update_led_state() {
	PORTA = led_state;
	for (unsigned char i = 0; i < 8; i++) {
		if ((led_state & (1 << i)) == 0) {
			lcdNumber(1, 11, i);
			char message[10];
			sprintf(message, "%d LED ON\n", i);
			uart_send_string(message);
			break;
		}
	}
}

ISR(INT0_vect) {
	uart_send_string("RESET\n");
	x = ~0;
	num_LCD = 0;
	PORTA = 0xFF;
	PORTD = 0xFF;
}

int main(void) {
	UBRR0L = 16; UBRR0H = 0;
	UCSR0A = 0x20;
	UCSR0B = 0x98;
	UCSR0C = 0x06;

	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;

	sei();

	DDRA = 0xFF;
	DDRD = 0x00;

	PORTA = 0xFF;
	PORTD = 0xFF;
	
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01) | (0 << ISC00);
	
	sei();

	while (1) {
		if (num_LCD != 0xFF) {
			if (num_LCD >= 48 && num_LCD <= 55) {
				unsigned char led_num = num_LCD - 48;
				led_state = ~(1 << led_num);
				update_led_state();
			}
			if (num_LCD == 56) {
				led_state = (led_state >> 1) | (led_state << 7);
				uart_send_string("LEFT\n");
				PORTA = led_state;
				} else if (num_LCD == 57) {
				led_state = (led_state << 1) | (led_state >> 7);
				uart_send_string("RIGHT\n");
				PORTA = led_state;
			}
			num_LCD = 0xFF;
		}
		_delay_ms(100);
	}
}

void uart_init(unsigned int ubrr) {
	UCSR0A |= _BV(U2X0);
	UBRR0H = 0x00;
	UBRR0L = 0x16;
	UCSR0C |= 0x06;
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void uart_send(unsigned char data_send) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data_send;
}

void uart_send_string(const char *str) {
	while (*str) {
		uart_send(*str++);
	}
}