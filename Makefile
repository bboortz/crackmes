#
# *** Configuration ***
#
NOSTD 				?= 1
STATIC 				?= 1
OPTIMIZATION 	?= SIZE
# SIZE 			- optimization for small binary size
# DEBUG 		- optimization for good debugging expierience
# NO 				- no compiler optimization
# DEFAULT		- normal compiler optimization


# 
# *** Compiler ***
#
CC = gcc
OBJCONV = objconv
ASM = nasm


# 
# *** Compiler flags ***
#

CFLAGS_ERROR = -Wall -Wextra -Wpedantic -Werror
# -Wall 			- enables all errors
# -Wextra 		- enables some extra warning flags that are not enabled by -Wall
# -Wpedantic 	- ensures strict ISO C
# -Werror 		- makes all warnings into errors

CFLAGS_STD = -std=c99 -m32
# -std=c99 	- define the C standard that the compiler supports
# -m32 			- compile for a 32 bit environment

ifeq ($(strip $(OPTIMIZATION)), SIZE)
CFLAGS_OPTIMIZATIONS = -Os -s -g0 -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-asynchronous-unwind-tables
# -Os 														- optimize for size
# -s - remove all symbol table and relocation information from the executable
# -g0 - no debugging information
# -ffunction-sections 						- place each function or data item into its own section in the output file
# -fdata-sections 								- place each function or data item into its own section 
# -Wl,--gc-sections 							- remove unused sections which produce smaller statically linked executables
# -fno-asynchronous-unwind-tables - generate unwind table in DWARF format which creates ~5% smaller results
 else ifeq ($(strip $(OPTIMIZATION)), DEBUG)
CFLAGS_OPTIMIZATIONS = -Og
# -Og 														- optimize for good debugging experience
else ifeq ($(strip $(OPTIMIZATION)), NO)
CFLAGS_OPTIMIZATIONS = -O0
# -O0 														- disable all optimizations
else
CFLAGS_OPTIMIZATIONS = -O2
# -O2 														- optimization which does not negatively affect the speed
endif

CFLAGS_NO_LINKER = -c
# -c 			- dont run the linker

ifeq ($(strip $(NOSTD)), 1)
CFLAGS_STDLIB = -nostdlib -fno-stack-protector
# -nostdlib - do not link the standard c library
# -fno-stack-protector 						- disable compiler stack protection
else
CFLAGS_STDLIB = 
endif

ifeq ($(strip $(STATIC)), 1)
CFLAGS_LINKER = $(CFLAGS_STDLIB) -static 
# -static - use static linking instead of dynamic linking
else
CFLAGS_LINKER = $(CFLAGS_STDLIB)
endif

CFLAGS_TO_ASM = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_NO_LINKER) -S
# -S - create assembly output
CFLAGS_TO_OBJ = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_NO_LINKER) 
CFLAGS_TO_EXE = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_LINKER) 
#OBJCONVFLAGS = -fnasm -wex -xs
#ASMFLAGS = -felf32

# Source file
SOURCE = crackme.c

# Output file
OUTPUT = crackme

all: $(OUTPUT) analysis

$(OUTPUT): $(SOURCE)
# 1088  gcc -S -o crackme.s crackme.c
# 1089  gcc -c crackme.s -o program.o
	$(CC) $(CFLAGS_TO_ASM) -o $@.s $<
	$(CC) $(CFLAGS_TO_OBJ) -o $@.o $@.s
	$(CC) $(CFLAGS_TO_EXE) -o $@ $@.o
	exit

# OLD way
#	$(CC) $(CFLAGS_OBJ) -o $@.o $<
#	# $(CC) $(CFLAGS_EXE) -o $@.exe $<
#	$(OBJCONV) $(OBJCONVFLAGS) $@.o $@.s
#	$(ASM) $(ASMFLAGS) -o $@.obj $@.s
#	$(CC) $(CFLAGS_EXE) -o $@ $@.obj

ifeq ($(strip $(OPTIMIZATION)), SIZE)
	strip --strip-all $@
	strip --strip-all -R .note -R .comment $@
	strip --strip-unneeded -R .note -R .comment $@
	strip --remove-section=.note.gnu.build-id $@
	strip --remove-section=.note.gnu.property $@
endif

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

