#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define RED_LED PORTA1
#define BLUE_LED PORTA3
#define GREEN_LED PORTA2

#define OVERFLOW_LED BLUE_LED
#define OVERFLOW_BLINK_TIME_CYCLES 2000

static bool _overflowLedEnabled = false;

void ledOn(int port)
{
   PORTA &= ~_BV(port);
}

void ledOff(int port)
{
   PORTA |= _BV(port);
}

int main (void)
{
    PORTA = 0x0;
    // Set direction of LED pins
    DDRA = 0x0;
    DDRA |= _BV(RED_LED);
    DDRA |= _BV(BLUE_LED);
    DDRA |= _BV(GREEN_LED);

    // Setup 16bit Timer (Timer1)
    // Set to normal mode
    TCCR1A = 0x0;
    TCCR1B = 0x0;
    // No Prescalar
    TCCR1B |= _BV(CS10);
    //TCCR1B |= _BV(CS11);
    //TCCR1B |= _BV(CS12);

    // Set Timer1 Overflow Interrupt Enable
    TIMSK1 = 0x0;
    TIMSK1 |= TOIE1;

    // Enable global interrupt flag
    sei();

    ledOff(RED_LED);
    ledOff(GREEN_LED);
    ledOff(BLUE_LED);

    while(1)
    {
        if (_overflowLedEnabled)
        {
            int timer = TCNT1;
            if (timer >= OVERFLOW_BLINK_TIME_CYCLES)
            {
                //ledOff(OVERFLOW_LED);
                _overflowLedEnabled = false;
            }
        }
    }
}

// Timer1 Overflow Interrupt Vector
ISR(TIM1_OVF_vect)
{
   // Disable global interrupt flag to do work
   cli();
   ledOn(OVERFLOW_LED);
   _overflowLedEnabled = true;
   // Re-enable global interrupt flag
   sei();
}
