# Compiler
CC = gcc
OBJCONV = objconv
ASM = nasm

# Compiler flags
#CFLAGS = -Wall -Wextra -Wpedantic -Werror -Wno-implicit-function-declaration -std=c99 -static -nostdlib -O0 -s -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-stack-protector -fno-asynchronous-unwind-tables -c
CFLAGS_ERROR = -Wall -Wextra -Wpedantic -Werror -Wno-implicit-function-declaration 
CFLAGS_STD = -std=c99 -nostdlib -m32
# -O2
CFLAGS_OPTIMIZATIONS = -O0 -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-stack-protector -fno-asynchronous-unwind-tables
# -g0
CFLAGS_STRIP = -s -g0
CFLAGS_OBJ = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_STRIP) -static -c
CFLAGS_EXE = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_STRIP) -static
OBJCONVFLAGS = -fnasm -wex -xs
ASMFLAGS = -felf32

# Source file
SOURCE = crackme.c

# Output file
OUTPUT = crackme

all: $(OUTPUT) analysis

$(OUTPUT): $(SOURCE)
	$(CC) $(CFLAGS_OBJ) -o $@.o $<
	# $(CC) $(CFLAGS_EXE) -o $@.exe $<
	$(OBJCONV) $(OBJCONVFLAGS) $@.o $@.s
	$(ASM) $(ASMFLAGS) -o $@.obj $@.s
	$(CC) $(CFLAGS_EXE) -o $@ $@.obj
	strip --strip-all $@
	strip --remove-section=.note.gnu.build-id $@

clean:
	rm -f $(OUTPUT) $(OUTPUT).o $(OUTPUT).obj $(OUTPUT).s
	rm -rf analysis

analysis:
	mkdir -p analysis
	ls -la $(OUTPUT)* > analysis/$(OUTPUT).ls
	du -shc $(OUTPUT)* > analysis/$(OUTPUT).du
	file $(OUTPUT)* > analysis/$(OUTPUT).file
	strings $(OUTPUT) > analysis/$(OUTPUT).strings
	ldd $(OUTPUT) > analysis/$(OUTPUT).ldd 2>&1 || true
	nm $(OUTPUT) > analysis/$(OUTPUT).nm 2>&1 || true
	objdump -x -t $(OUTPUT) > analysis/$(OUTPUT).objdump-headers || true
	objdump -S $(OUTPUT) > analysis/$(OUTPUT).objdump-sources || true
	readelf -a $(OUTPUT) > analysis/$(OUTPUT).readelf || true

