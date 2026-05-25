#define F_CPU 16000000UL

#include <avr/io.h>

int main(void)
{
    // Set PB0 as output
    DDRB |= (1 << DDB0);

    // Set PD2 as input
    DDRD &= ~(1 << DDD2);

    // Enable pull-up resistor on PD2 (optional but recommended)
    PORTD |= (1 << PD2);

    while (1)
    {
        // If button on PD2 is pressed (logic LOW)
        if (PIND & (1 << PD2))
        {
            // Turn OFF LED (PB0)
            PORTB &= ~(1 << PB0);
        }
        else
        {
            // Turn ON LED (PB0)
            PORTB |= (1 << PB0);
        }
    }

    return 0;
}