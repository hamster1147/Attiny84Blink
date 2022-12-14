#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_MAX 65536
#define F_CPU 8000000UL // 8 MHz
#define TIMER1_PRESCALAR 1024
#define F_TIMER1 F_CPU / TIMER1_PRESCALAR // 7,812.5 Hz

#define RED_LED PORTA1
#define BLUE_LED PORTA3
#define GREEN_LED PORTA2

#define BLINK_DURATION_COUNT (0.1 * F_TIMER1) // 0.1 seconds

#define OVERFLOW_LED BLUE_LED

#define BLINK_COUNT_MAX 5
#define BLINK_LED RED_LED
#define BLINK_INTERVAL_COUNT (3.0 * F_TIMER1) // 3.0 seconds

static unsigned char _overflowed = 0;

void ledSet(int port)
{
   PORTA &= ~_BV(port);
}

void ledClear(int port)
{
   PORTA |= _BV(port);
}

void ledToggle(int port)
{
   PORTA ^= _BV(port);
}

// Timer1 Overflow Interrupt Vector
ISR(TIM1_OVF_vect)
{
   cli(); // Disable global interrupt flag to do work
   ledToggle(OVERFLOW_LED);
   _overflowed = 1;
   sei(); // Re-enable global interrupt flag
}

int main (void)
{
   unsigned char totalBlinks = 0;
   unsigned long nextOnCount = BLINK_INTERVAL_COUNT;
   unsigned long nextOffCount = BLINK_INTERVAL_COUNT + BLINK_DURATION_COUNT;

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
   TCNT1  = 0x0; // Reset Timer
   GTCCR  = _BV(PSR10); // Reset prescaler
   OCR1A  = 4000; // Set compare to MAX to reset timer
   OCR1B  = 4000;
   TIMSK1 = _BV(TOIE1); // Set Timer1 Compare A Interrupt Enable
   // 1024 Prescalar
   TCCR1B |= _BV(CS10);
   TCCR1B |= _BV(CS12);

   sei(); // Enable global interrupt flag

   ledClear(RED_LED);
   ledClear(GREEN_LED);
   ledClear(BLUE_LED);

   while(1)
   {
      if (_overflowed)
      {
         nextOnCount -= TIMER_MAX;
         nextOffCount -= TIMER_MAX;
         _overflowed = 0;
      }

      unsigned long timer = TCNT1;
      if (totalBlinks < BLINK_COUNT_MAX)
      {
         if (timer >= nextOnCount)
         {
            ledSet(BLINK_LED);
            nextOnCount = nextOnCount + BLINK_INTERVAL_COUNT;
         }

         if (timer >= nextOffCount)
         {
            ledClear(BLINK_LED);
            nextOffCount = nextOffCount + BLINK_INTERVAL_COUNT;
            totalBlinks++;
         }
      }
   }
}
