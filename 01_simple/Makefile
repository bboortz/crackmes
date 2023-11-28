# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -static -Os -s -ffunction-sections -fdata-sections -Wl,--gc-sections

# Source file
SOURCE = crackme.c

# Output file
OUTPUT = crackme

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCE)

clean:
	rm -f $(OUTPUT)

