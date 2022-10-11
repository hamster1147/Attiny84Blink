#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define F_CPU 8000000UL // 8 MHz
#define TIMER1_PRESCALAR 1024
#define F_TIMER1 F_CPU / TIMER1_PRESCALAR // 7,812.5 Hz

#define RED_LED PORTA1
#define BLUE_LED PORTA3
#define GREEN_LED PORTA2

#define BLINK_DURATION_COUNT (0.1 * F_TIMER1) // 0.1 seconds

#define OVERFLOW_LED BLUE_LED

#define BLINK_LED RED_LED
#define BLINK_INTERVAL_COUNT ((F_TIMER1 * 3.0) / 5.0)

static bool _overflowLedEnabled = false;

void ledOn(int port)
{
   PORTA &= ~_BV(port);
}

void ledOff(int port)
{
   PORTA |= _BV(port);
}

// Timer1 Overflow Interrupt Vector
ISR(TIM1_OVF_vect)
{
   cli(); // Disable global interrupt flag to do work
   ledOn(OVERFLOW_LED);
   _overflowLedEnabled = true;
   sei(); // Re-enable global interrupt flag
}

int main (void)
{
    int nextOnCount = BLINK_INTERVAL_COUNT;
    int nextOffCount = BLINK_INTERVAL_COUNT + BLINK_DURATION_COUNT;

    PORTA = 0x0;
    // Set direction of LED pins
    DDRA = 0x0;
    DDRA |= _BV(RED_LED);
    DDRA |= _BV(BLUE_LED);
    DDRA |= _BV(GREEN_LED);

    // Setup 16bit Timer (Timer1)
    TCCR1A = 0x0; // Stop Timer
    TCCR1B = 0x0; // Stop Timer
    TCCR1C = 0x0; // Stop Timer
    TCNT1 = 0x0; // Reset Timer
    GTCCR = _BV(PSR10); // Reset prescaler
    OCR1A = 4000; // Set compare to MAX to reset timer
    OCR1B = 4000;
    TIMSK1 = 0x0;
    TIMSK1 |= _BV(TOIE1); // Set Timer1 Compare A Interrupt Enable
    //TIMSK1 = 0x0;
    TCCR1B = 0x0;
    //TCCR1B |= _BV(WGM12); // Enable Clear Timer on Compare mode
    // 1024 Prescalar
    TCCR1B |= _BV(CS10);
    //TCCR1B |= _BV(CS11);
    TCCR1B |= _BV(CS12);

    sei(); // Enable global interrupt flag

    ledOff(RED_LED);
    ledOff(GREEN_LED);
    ledOff(BLUE_LED);

    while(1)
    {
        int timer = TCNT1;
        if (timer >= nextOnCount)
        {
            ledOn(BLINK_LED);
            nextOnCount += BLINK_INTERVAL_COUNT;
        }

        if (timer >= nextOffCount)
        {
            ledOff(BLINK_LED);
            nextOffCount = nextOnCount + BLINK_DURATION_COUNT;
        }

        if (_overflowLedEnabled)
        {
            if (timer >= BLINK_DURATION_COUNT)
            {
                ledOff(OVERFLOW_LED);
                _overflowLedEnabled = false;
            }
        }
    }
}
