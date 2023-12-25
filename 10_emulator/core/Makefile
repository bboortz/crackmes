#
# *** Targets  ***
#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#


#
# *** Configuration ***
#
NOSTD 			?= 0
STATIC 			?= 0
OPTIMIZATION 	?= DEBUG
# SIZE 			- optimization for small binary size
# DEBUG 		- optimization for good debugging expierience
# NO 				- no compiler optimization
# DEFAULT		- normal compiler optimization


#
# *** Compiler flags ***
#
CFLAGS_SPECIAL := # -fno-stack-protector -no-pie

CFLAGS_ERROR = -Wall -Wextra -Wpedantic -Werror
# -Wall 		- enables all errors
# -Wextra 		- enables some extra warning flags that are not enabled by -Wall
# -Wpedantic 	- ensures strict ISO C
# -Werror 		- makes all warnings into errors

CFLAGS_STD = -std=c17 -m64
# -std=c99 	- define the C standard that the compiler supports
# -m32 			- compile for a 32 bit environment

ifeq ($(strip $(OPTIMIZATION)), SIZE)
CFLAGS_OPTIMIZATIONS = -Os -s -g0 -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-asynchronous-unwind-tables
# -Os								- optimize for size
# -s 								- remove all symbol table and relocation information from the executable
# -g0 								- no debugging information
# -ffunction-sections 				- place each function or data item into its own section in the output file
# -fdata-sections 					- place each function or data item into its own section
# -Wl,--gc-sections 				- remove unused sections which produce smaller statically linked executables
# -fno-asynchronous-unwind-tables 	- generate unwind table in DWARF format which creates ~5% smaller results
# -fno-stack-protector 						- disable the gcc stack protection with canaries
 else ifeq ($(strip $(OPTIMIZATION)), DEBUG)
CFLAGS_OPTIMIZATIONS = -Og -g -rdynamic
# -Og 		- optimize for good debugging experience
# -g		- Produce debugging information in the operating system's native format
# -rdynamic - This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of "dlopen" or to allow obtaining backtraces from within a program.
else ifeq ($(strip $(OPTIMIZATION)), NO)
CFLAGS_OPTIMIZATIONS = -O0
# -O0 		- disable all optimizations
else
CFLAGS_OPTIMIZATIONS = -O2
# -O2 		- optimization which does not negatively affect the speed
endif

CFLAGS_NO_LINKER = -c
# -c 			- dont run the linker

ifeq ($(strip $(NOSTD)), 1)
CFLAGS_STDLIB = -nostdlib -fno-stack-protector
# -nostdlib 			- do not link the standard c library
# -fno-stack-protector 	- disable compiler stack protection
else
CFLAGS_STDLIB =
endif

ifeq ($(strip $(STATIC)), 1)
CFLAGS_LINKER = $(CFLAGS_STDLIB) -static
# -static - use static linking instead of dynamic linking
else
CFLAGS_LINKER = $(CFLAGS_STDLIB)
endif

CFLAGS_TO_ASM = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_SPECIAL) $(CFLAGS_NO_LINKER) -S
# -S - create assembly output
CFLAGS_TO_OBJ = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_SPECIAL) $(CFLAGS_NO_LINKER)
CFLAGS_TO_EXE = $(CFLAGS_ERROR) $(CFLAGS_STD) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_SPECIAL) $(CFLAGS_LINKER)


#
# *** Pathes and Flags ***
#

# define the C compiler to use
CC = gcc
# CC = tests_include/afl/afl-gcc # gcc

# tar
TAR = tar

# define any compile-time flags
#CFLAGS	:= -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define test directory
TESTSRC	:= tests

# define include directory
INCLUDE	:= include
TESTINCLUDE := ../tests_include/unity/src

# define lib directory
LIB		:= lib
TESTLIB := ../tests_lib

ifeq ($(OS),Windows_NT)
MAIN	:= crackme.exe
MAINTEST	:= test.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
TESTINCLUDEDIRS	:= $(TESTINCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= crackme
TESTCSTACK   := test_cstack
TESTCHEAP   := test_cheap
TESTCERROR   := test_cerror
TESTCSTRING   := test_cstring
TESTCCHARP   := test_ccharp
SOURCEDIRS	:= $(shell find $(SRC) -type d)
TESTSOURCEDIRS	:= $(shell find $(TESTSRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
TESTINCLUDEDIRS	:= $(shell find $(TESTINCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
TESTLIBDIRS		:= $(shell find $(TESTLIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
TESTINCLUDES	:= $(patsubst %,-I%, $(TESTINCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
TESTLIBS		:= $(patsubst %,-L%, $(TESTLIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
TESTSOURCES		:= $(wildcard $(patsubst %,%/*.c, $(TESTSOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.c=.o)
TESTOBJECTS		:= $(TESTSOURCES:.c=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)
TESTDEPS		:= $(TESTOBJECTS:.o=.d)

TESTOBJECTSUNITY := ../tests_include/unity/CMakeFiles/unity.dir/src/unity.c.o


#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

TESTOUTPUTCSTACK		:= $(call FIXPATH,$(OUTPUT)/$(TESTCSTACK))
TESTOUTPUTCHEAP		:= $(call FIXPATH,$(OUTPUT)/$(TESTCHEAP))
TESTOUTPUTCERROR		:= $(call FIXPATH,$(OUTPUT)/$(TESTCERROR))
TESTOUTPUTCSTRING		:= $(call FIXPATH,$(OUTPUT)/$(TESTCSTRING))
TESTOUTPUTCCHARP		:= $(call FIXPATH,$(OUTPUT)/$(TESTCCHARP))


$(OUTPUT):
	$(MD) $(OUTPUT)

compileobjects: $(OBJECTS)
	@echo Objects compiled!

compiletestobjects: compileobjects

$(TESTCSTACK): compiletestobjects
	$(CC) $(CFLAGS_TO_EXE) $(INCLUDES) $(TESTINCLUDES) -o $(TESTOUTPUTCSTACK) $(OBJECTS) tests/test_cstack.c $(TESTOBJECTSUNITY) $(LFLAGS) $(TESTLIBS)

$(TESTCHEAP): compiletestobjects
	$(CC) $(CFLAGS_TO_EXE) $(INCLUDES) $(TESTINCLUDES) -o $(TESTOUTPUTCHEAP) $(OBJECTS) tests/test_cheap.c $(TESTOBJECTSUNITY) $(LFLAGS) $(TESTLIBS)

$(TESTCERROR): compiletestobjects
	$(CC) $(CFLAGS_TO_EXE) $(INCLUDES) $(TESTINCLUDES) -o $(TESTOUTPUTCERROR) $(OBJECTS) tests/test_cerror.c $(TESTOBJECTSUNITY) $(LFLAGS) $(TESTLIBS)

$(TESTCSTRING): compiletestobjects
	$(CC) $(CFLAGS_TO_EXE) $(INCLUDES) $(TESTINCLUDES) -o $(TESTOUTPUTCSTRING) $(OBJECTS) tests/test_cstring.c $(TESTOBJECTSUNITY) $(LFLAGS) $(TESTLIBS)

$(TESTCCHARP): compiletestobjects
	$(CC) $(CFLAGS_TO_EXE) $(INCLUDES) $(TESTINCLUDES) -o $(TESTOUTPUTCCHARP) $(OBJECTS) tests/test_ccharp.c $(TESTOBJECTSUNITY) $(LFLAGS) $(TESTLIBS)


test: compiletestobjects $(TESTCSTACK) $(TESTCHEAP) $(TESTCERROR) $(TESTCSTRING) $(TESTCCHARP)
	@echo Tests compiled!


# include all .d files
-include $(DEPS)

# this is a suffix replacement rule for building .o's and .d's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# -MMD generates dependency output files same name as the .o file
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS_TO_OBJ) $(INCLUDES) -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(TESTOUTPUTCMAIN)
	$(RM) $(TESTOUTPUTCSTACK)
	$(RM) $(TESTOUTPUTCHEAP)
	$(RM) $(TESTOUTPUTCERROR)
	$(RM) $(TESTOUTPUTCSTRING)
	$(RM) $(TESTOUTPUTCCHARP)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(TESTOBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	$(RM) $(call FIXPATH,$(TESTDEPS))
	$(RM) analysis/*
	$(RM) build/Debug/*
	@echo Cleanup complete!

all: compileobjects test
ifneq ($(strip $(OPTIMIZATION)), DEBUG)
	strip --strip-all $(OUTPUTMAIN)
	strip --strip-all -R .note -R .comment $(OUTPUTMAIN)
	strip --strip-unneeded -R .note -R .comment $(OUTPUTMAIN)
	strip --remove-section=.note.gnu.build-id $(OUTPUTMAIN)
	strip --remove-section=.note.gnu.property $(OUTPUTMAIN)
endif
	@echo Executing 'all' complete!

tar: all
	$(TAR) zcvf $(MAIN).tar.gz README.md SOLUTION.md -C output crackme

analysis: all
	mkdir -p analysis
	ls -la $(OUTPUTMAIN)* > analysis/$(MAIN).ls
	du -shc $(OUTPUTMAIN)* > analysis/$(MAIN).du
	file $(OUTPUTMAIN)* > analysis/$(MAIN).file
	strings $(OUTPUTMAIN) > analysis/$(MAIN).strings
	ldd $(OUTPUTMAIN) > analysis/$(MAIN).ldd 2>&1 || true
	nm $(OUTPUTMAIN) > analysis/$(MAIN).nm 2>&1 || true
	objdump -x -t $(OUTPUTMAIN) > analysis/$(MAIN).objdump-headers || true
	objdump -S $(OUTPUTMAIN) > analysis/$(MAIN).objdump-sources || true
	readelf -a $(OUTPUTMAIN) > analysis/$(MAIN).readelf || true

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!

runtests: compileobjects $(TESTMAIN)
	./tests.sh
	@echo Executing 'run: all' complete!
