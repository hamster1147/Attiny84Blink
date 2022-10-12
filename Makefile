PRJ = blink_led
MCU = attiny84
CLK = 8000000
PRG = usbtiny
SRC = $(PRJ).c

LFU = 0xE2
HFU = 0xDF
EFU = 0xFF

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

fuse:
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m
