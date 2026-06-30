#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// UART setup
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (16UL * BAUD)) - 1)

void UART_Init(void)
{
    UBRR0H = (uint8_t)(BAUD_PRESCALE >> 8);
    UBRR0L = (uint8_t)(BAUD_PRESCALE);

    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_Transmit(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART_Print(char *str)
{
    while (*str)
        UART_Transmit(*str++);
}

// ADC Init
void ADC_Init(void)
{
    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADEN)  |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);

    // Dummy conversion to warm up ADC after enable
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
}

// ADC Read with MUX settling + dummy read
uint16_t ADC_Read(uint8_t channel)
{
    channel &= 0x07;
    ADMUX = (ADMUX & 0xF8) | channel;

    _delay_us(10);

    // Dummy read — discard result
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    (void)ADC;

    // Real read
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADC;
}

int main(void)
{
    uint16_t ldrValue;
    uint16_t potValue;
    uint16_t gasValue;

    uint16_t gasThreshold = 175;
    char buffer[40];

    DDRD |= (1 << PD2);
    DDRD |= (1 << PD3);

    UART_Init();
    ADC_Init();

    while (1)
    {
        ldrValue = ADC_Read(0);
        potValue = ADC_Read(1);
        gasValue = ADC_Read(2);

        // Print all values on one line
        sprintf(buffer, "LDR:%4u | POT:%4u | GAS:%4u\r\n", ldrValue, potValue, gasValue);
        UART_Print(buffer);

        _delay_ms(500);

        if (ldrValue < potValue)
            PORTD |= (1 << PD2);
        else
            PORTD &= ~(1 << PD2);

        if (gasValue > gasThreshold)
            PORTD |= (1 << PD3);
        else
            PORTD &= ~(1 << PD3);
    }
}