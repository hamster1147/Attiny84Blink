### Resources:
https://gcc.gnu.org/wiki/HomePage
https://ww1.microchip.com/downloads/en/DeviceDoc/doc8006.pdf
http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny84
https://gist.github.com/mcous/5920089

### Issues in order:
- Getting Linux laptop working again
- Remembering how to make a Makefile
- Realizing controlling the LED was inverted
- Making sure fuses were correct.
- Getting Timer1 to work (I messed up a few bit settings). I learned that turning on the Compare A interrupt seemed to force the Timer into CTC mode.
- Realizing that ints are 2 bytes
- Realizing that I didn't use an unsigned long on the timer polling. (I assume this is the big issue Glenn caught in his email)
- Working out a solution for setting/checking timer count values that go beyond the max timer count.