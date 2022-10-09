```
sudo apt-get install gcc-avr binutils-avr avr-libc
sudo apt-get install avrdude
```

```
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blink_led.o blink_led.c
avr-gcc -mmcu=atmega328p blink_led.o -o blink_led
avr-objcopy -O ihex -R .eeprom blink_led blink_led.hex
avrdude -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:blink_led.hex:i
```
