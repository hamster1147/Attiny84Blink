PRJ = blink_led
MCU = attiny85
CLK = 16000000
PRG = usbtiny
SRC = $(PRJ).c

CC     = avr-gcc
CFLAGS = -Wall -Os -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE)

AVRDUDE = avrdude -c $(PRG) -p $(MCU)
OBJCOPY = avr-objcopy
SIZE    = avr-size --format=avr --mcu=$(MCU)

# generate list of objects
CFILES    = $(filter %.c, $(SRC))
OBJ       = $(CFILES:.c=.o)

all: $(PRJ).hex

# flash program to mcu
flash: all
	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

$(PRJ).o: $(PRJ).c
	$(CC) $(CFLAGS) -c $< -o $@

# elf file
$(PRJ).elf: $(PRJ).o
	$(CC) $(CFLAGS) -o $(PRJ).elf $(OBJ)

# hex file
$(PRJ).hex: $(PRJ).elf
	rm -f $(PRJ).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	$(SIZE) $(PRJ).elf

clean:
	rm -f *.hex *.elf *.o
	$(foreach dir, $(EXT), rm -f $(dir)/*.o;)
