#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define RED_LED PORTA1
#define BLUE_LED PORTA3
#define GREEN_LED PORTA2

#define OVERFLOW_LED BLUE_LED
#define OVERFLOW_BLINK_TIME_CYCLES 2000

int main (void)
{
    bool overflowLedEnabled = false;

    /*Set to one the fifth bit of DDRB to one
    **Set digital pin 13 to output mode */
    DDRB |= _BV(DDB3);

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

    while(1)
    {
        if (overflowLedEnabled)
        {
            int timer = TCNT1;
            if (timer >= OVERFLOW_BLINK_TIME_CYCLES)
            {
                PORTB &= ~_BV(OVERFLOW_LED);
                overflowLedEnabled = false;
            }
        }
    }

    // Timer1 Overflow Interrupt Vector
    ISR(TIM1_OVF_vect)
    {
        cli();
        PORTB |= _BV(OVERFLOW_LED);
        overflowLedEnabled = true;
        sei();
    }
}
