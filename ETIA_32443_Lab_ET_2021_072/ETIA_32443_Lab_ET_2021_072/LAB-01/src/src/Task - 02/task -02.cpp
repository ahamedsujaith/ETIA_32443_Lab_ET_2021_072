#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Set PB0 as output pin
    DDRB |= (1 << DDB0);

    while (1)
    {   
        // LED ON (PB0 HIGH)
        PORTB |= (1 << PB0);
        _delay_ms(1000);

        // LED OFF (PB0 LOW)
        PORTB &= ~(1 << PB0);
        _delay_ms(1000);
    }

    return 0;
}

/*The LED connected to PB0 is toggled ON and OFF using PORTB register. 
The delay function _delay_ms(1000) creates a visible 1-second blink interval.*/