### Resources:
- https://create.arduino.cc/projecthub/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
- https://gcc.gnu.org/wiki/HomePage
- https://ww1.microchip.com/downloads/en/DeviceDoc/doc8006.pdf
- http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny84
- https://gist.github.com/mcous/5920089

### Issues in order:
- Getting Linux laptop working again
- Remembering how to make a Makefile
- Realizing controlling the LED was inverted
- Making sure fuses were correct.
- Getting Timer1 to work (I messed up a few bit settings). I learned that turning on the Compare A interrupt seemed to force the Timer into CTC mode.
- Realizing that ints are 2 bytes
- Realizing that I didn't use an unsigned long on the timer polling. (I assume this is the big issue Glenn caught in his email)
- Working out a solution for setting/checking timer count values that go beyond the max timer count.

### Setup used:
![](https://github.com/hamster1147/Attiny84Blink/blob/develop/Media/Attiny84Blink.PNG?raw=true)

### Demonstration:
https://user-images.githubusercontent.com/6164680/195229787-0c508aed-c733-4ed7-8139-129e64502e17.mov
