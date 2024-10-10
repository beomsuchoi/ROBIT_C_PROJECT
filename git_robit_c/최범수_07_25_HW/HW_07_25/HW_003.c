/*
 * test5.c
 *
 * Created: 2024-07-28 오전 4:25:21
 * Author : chlqj
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void pattern1() {
    uint8_t patterns[] = {248, 241, 227, 199, 143, 31, 62, 124};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 7; j++) {
            PORTA = patterns[j];
            _delay_ms(100);
        }
    }
}

void pattern2() {
    uint8_t patterns[] = {31, 143, 199, 227, 241, 248, 124, 62};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            PORTA = patterns[j];
            _delay_ms(100);
        }
    }
}

void pattern3() {
    int result_first = 1;
    for(int i = 0; i < 8; i++) {
        PORTA = ~result_first;
        _delay_ms(100);
        result_first *= 2;
    }
    
    int result_second = 128;
    for(int i = 0; i < 8; i++) {
        PORTA = ~result_second;
        _delay_ms(100);
        result_second /= 2;
    }
}

ISR(INT0_vect) {
    pattern1();
}

ISR(INT1_vect) {
    pattern2();
}

ISR(INT2_vect) {
    pattern3();
}

ISR(INT3_vect) {
}

void setupInterrupts() {
    EIMSK |= (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3);
    EICRA |= (1 << ISC01) | (1 << ISC11) | (1 << ISC21) | (1 << ISC31);
}

int main(void) {
    DDRA = 0xFF;
    DDRD = 0x00;
    
    setupInterrupts();
    sei();
    
    int x = 255;
    while (1) {
        PORTA = x;
        _delay_ms(100);
        x--;
    }
}