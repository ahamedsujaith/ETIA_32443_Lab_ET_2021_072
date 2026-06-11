#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

#define INITIAL_CAPACITY 10
#define DETECTION_DISTANCE 25

volatile uint8_t vehicles_entered = 0;
volatile uint8_t available_slots = INITIAL_CAPACITY;

uint8_t currentVehicleState = 0;
uint8_t previousVehicleState = 0;

//--------------------------------------------------
// Generate 10us Trigger Pulse
//--------------------------------------------------
void triggerUltrasonic(void)
{
    PORTB &= ~(1 << PB0);   // TRIG LOW
    _delay_us(2);

    PORTB |= (1 << PB0);    // TRIG HIGH
    _delay_us(10);

    PORTB &= ~(1 << PB0);   // TRIG LOW
}

//--------------------------------------------------
// Read Echo Pulse Width
//--------------------------------------------------
uint32_t readEchoTime(void)
{
    uint32_t count = 0;

    while (!(PINB & (1 << PB1)));

    while (PINB & (1 << PB1))
    {
        count++;
        _delay_us(1);
    }

    return count;
}

//--------------------------------------------------
// Calculate Distance
//--------------------------------------------------
uint16_t readDistance(void)
{
    triggerUltrasonic();

    uint32_t duration = readEchoTime();

    uint16_t distance = (duration * 34) / 2000;

    return distance;
}

//--------------------------------------------------
// LED Status Update
//--------------------------------------------------
void updateLEDs(void)
{
    PORTD &= ~((1<<PD5)|(1<<PD6)|(1<<PD7));

    if (available_slots > (INITIAL_CAPACITY/2))
    {
        PORTD |= (1<<PD5);      // Green ON
    }
    else if (available_slots > 0)
    {
        PORTD |= (1<<PD6);      // Yellow ON
    }
    else
    {
        PORTD |= (1<<PD7);      // Red ON
    }
}

//--------------------------------------------------
int main(void)
{
    // LEDs Output
    DDRD |= (1<<PD5) | (1<<PD6) | (1<<PD7);

    // Trigger Output
    DDRB |= (1<<PB0);

    // Echo Input
    DDRB &= ~(1<<PB1);

    // Reset Button Input
    DDRD &= ~(1<<PD2);

    // Internal Pull-up
    PORTD |= (1<<PD2);

    updateLEDs();

    while (1)
    {
        // Reset Button Pressed
        if (!(PIND & (1<<PD2)))
        {
            vehicles_entered = 0;
            available_slots = INITIAL_CAPACITY;

            updateLEDs();

            _delay_ms(300);
        }

        uint16_t distance = readDistance();

        if ((distance > 0) &&
            (distance < DETECTION_DISTANCE))
        {
            currentVehicleState = 1;
        }
        else
        {
            currentVehicleState = 0;
        }

        // State Change Detection
        if ((currentVehicleState == 1) &&
            (previousVehicleState == 0))
        {
            if (vehicles_entered < INITIAL_CAPACITY)
            {
                vehicles_entered++;

                available_slots =
                    INITIAL_CAPACITY - vehicles_entered;

                updateLEDs();
            }
        }

        previousVehicleState = currentVehicleState;

        _delay_ms(100);
    }
}