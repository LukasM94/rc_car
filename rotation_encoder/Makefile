
CC     = avr-g++
CC_HEX = avr-objcopy
SIZE   = avr-size

UCONTROLLER = attiny85

TARGET = main

SOURCE_DIR  = source
OBJECT_DIR  = object
INCLUDE_DIR = include
SHARED_DIR  = ../shared
RELEASE_DIR = release

OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o,$(wildcard $(SOURCE_DIR)/*.cpp)) 

FREQUENCY = 2000000

OPTIMIZATION = 3

GNU = 17

CFLAGS  = -mmcu=$(UCONTROLLER)
CFLAGS += -I./$(INCLUDE_DIR)
CFLAGS += -I$(SHARED_DIR)
CFLAGS += -DF_CPU=$(FREQUENCY)UL
CFLAGS += -O$(OPTIMIZATION) 
CFLAGS += -Wall
# CFLAGS += -Werror
CFLAGS += -Wundef
CFLAGS += -std=gnu++$(GNU)
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
# CFLAGS += -fpack-struct
CFLAGS += -fshort-enums

all: begin sizebefore compiling linking hex sizeafter end

$(OBJECT_DIR)/$(TARGET).o: $(TARGET).cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CC) -c $(CFLAGS) $< -o $@

begin:
	@echo "------------------begin--------------------"
	avr-gcc --version
	@if [ -z $(shell ls | grep $(OBJECT_DIR)) ]; then echo ; mkdir $(OBJECT_DIR); \
	echo "$(OBJECT_DIR) created"; else echo "$(OBJECT_DIR) still exists"; echo ""; fi
	@if [ -z $(shell ls | grep $(RELEASE_DIR)) ]; then echo ; mkdir $(RELEASE_DIR); \
	echo "$(RELEASE_DIR) created"; else echo "$(RELEASE_DIR) still exists"; echo ""; fi

end:
	@echo "-------------------end---------------------"

compiling: $(OBJECT_DIR)/$(TARGET).o $(OBJECTS)

linking:
	$(CC) $(CFLAGS) $(OBJECTS) $(OBJECT_DIR)/$(TARGET).o -o $(RELEASE_DIR)/$(TARGET).elf

hex: $(RELEASE_DIR)/$(TARGET).elf
	$(CC_HEX) -O ihex -R .eeprom $(RELEASE_DIR)/$(TARGET).elf $(RELEASE_DIR)/$(TARGET).hex

HEXSIZE = $(SIZE) $(RELEASE_DIR)/$(TARGET).hex
sizebefore:
	@if [ -f $(RELEASE_DIR)/$(TARGET).hex ]; then echo; echo "Size of the hex file before compiling"; $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f $(RELEASE_DIR)/$(TARGET).hex ]; then echo; echo "Size of the hex file after compiling"; $(HEXSIZE); echo; fi

EXISTING_OBJECTS = $(addprefix $(OBJECT_DIR)/, $(shell ls $(OBJECT_DIR)))
EXISTING_RELEASE = $(addprefix $(RELEASE_DIR)/, $(shell ls $(RELEASE_DIR)))
clean:
	@if [ ! -z "$(EXISTING_OBJECTS)" ]; then echo "rm $(EXISTING_OBJECTS)"; rm $(EXISTING_OBJECTS); fi
	@if [ ! -z "$(EXISTING_RELEASE)" ]; then echo "rm $(EXISTING_RELEASE)"; rm $(EXISTING_RELEASE); fi

# avr-gcc -c -mmcu=atmega328p -I ./include -D F_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Werror -Wundef -std=gnu11 main.c -o main.o
# avr-gcc -I./include -DF_CPU=16000000UL -Os  -Wall -Werror -Wundef -std=gnu11 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums   -c -o main.o main.c