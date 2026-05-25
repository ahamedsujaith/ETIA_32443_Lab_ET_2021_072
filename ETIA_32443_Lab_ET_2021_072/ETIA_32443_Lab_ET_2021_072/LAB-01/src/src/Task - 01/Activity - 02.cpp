#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

void task2()
{
    DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);

    // PC0
    PORTC |= (1 << PC0);
    _delay_ms(500);
    PORTC &= ~(1 << PC0);
    _delay_ms(500);

    // PC1
    PORTC |= (1 << PC1);
    _delay_ms(500);
    PORTC &= ~(1 << PC1);
    _delay_ms(500);

    // PC2
    PORTC |= (1 << PC2);
    _delay_ms(500);
    PORTC &= ~(1 << PC2);
    _delay_ms(500);

    // PC3
    PORTC |= (1 << PC3);
    _delay_ms(500);
    PORTC &= ~(1 << PC3);
    _delay_ms(500);
}