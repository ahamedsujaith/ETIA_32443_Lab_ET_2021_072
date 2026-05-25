#include <Arduino.h>
#include <avr/io.h>

#define PASSWORD_LENGTH 4

// Correct password
uint8_t password[PASSWORD_LENGTH] = {1, 2, 3, 4};

// Stores entered password
uint8_t entered[PASSWORD_LENGTH];

// Current position
uint8_t indexPos = 0;

// Function prototype
void buttonDelay();

void setup()
{
    // PB0 and PB1 as outputs (LEDs)
    DDRB |= (1 << PB0) | (1 << PB1);

    // LEDs OFF initially
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);

    // PD2-PD5 as inputs
    DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));

    // Enable internal pull-up resistors
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);
}

void loop()
{
    if (!(PIND & (1 << PD2)))
    {
        if (indexPos < PASSWORD_LENGTH)
        {
            entered[indexPos] = 1;
            indexPos++;
        }
        buttonDelay();
    }

    if (!(PIND & (1 << PD3)))
    {
        if (indexPos < PASSWORD_LENGTH)
        {
            entered[indexPos] = 2;
            indexPos++;
        }
        buttonDelay();
    }

    if (!(PIND & (1 << PD4)))
    {
        if (indexPos < PASSWORD_LENGTH)
        {
            entered[indexPos] = 3;
            indexPos++;
        }
        buttonDelay();
    }

    if (!(PIND & (1 << PD5)))
    {
        if (indexPos < PASSWORD_LENGTH)
        {
            entered[indexPos] = 4;
            indexPos++;
        }
        buttonDelay();
    }

    // Check password after 4 entries
    if (indexPos >= PASSWORD_LENGTH)
    {
        bool correct = true;

        for (uint8_t i = 0; i < PASSWORD_LENGTH; i++)
        {
            if (entered[i] != password[i])
            {
                correct = false;
                break;
            }
        }

        if (correct)
        {
            // Green LED ON
            PORTB |= (1 << PB0);
            PORTB &= ~(1 << PB1);
        }
        else
        {
            // Red LED ON
            PORTB |= (1 << PB1);
            PORTB &= ~(1 << PB0);
        }

        delay(3000);

        // LEDs OFF
        PORTB &= ~(1 << PB0);
        PORTB &= ~(1 << PB1);

        // Reset password entry
        indexPos = 0;

        for (uint8_t i = 0; i < PASSWORD_LENGTH; i++)
        {
            entered[i] = 0;
        }
    }
}

void buttonDelay()
{
    delay(300);
}