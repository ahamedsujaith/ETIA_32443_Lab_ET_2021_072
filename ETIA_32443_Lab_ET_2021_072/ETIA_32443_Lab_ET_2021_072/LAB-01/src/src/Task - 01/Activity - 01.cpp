#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

void task1()
{
    DDRB |= (1 << DDB0);   // PB0 output

    PORTB |= (1 << PB0);
    _delay_ms(1000);

    PORTB &= ~(1 << PB0);
    _delay_ms(1000);
}