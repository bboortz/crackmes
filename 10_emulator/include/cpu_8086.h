#ifndef CPU_6502_H
#define CPU_6502_H

#include <stdint.h>
#include "cpu.h"
#include "parser.h"


// Define a constant representing the maximum memory size for the CPU 6502
#define CPU_6502_MAX_MEM 1024 * 64
#define CPU_6502_MEM_ZERO_PAGE_MIN 0x0000
#define CPU_6502_MEM_ZERO_PAGE_MAX 0x00FF
#define CPU_6502_MEM_STACK_MIN 0x0100
#define CPU_6502_MEM_STACK_MAX 0x01FF
#define CPU_6502_MEM_NORMAL_MIN 0x0200
#define CPU_6502_MEM_NORMAL_MAX 0xFFF9
#define CPU_6502_MEM_RESERVED_MIN 0xFFFA
#define CPU_6502_MEM_RESERVED_MAX 0xFFFF


// Define a struct representing the memory of CPU 6502
typedef struct {
    unsigned char data[CPU_6502_MAX_MEM];  // Array to hold CPU memory data
} cpu_8086_mem;


// Define a struct representing CPU 6502
typedef struct {
    cpu_type type;
    uint16_t ip;            // Instruction pointer = program counter
    uint16_t sp;            // Stack pointer
    unsigned char reg_a;    // Register A
    unsigned char reg_x;    // Register X
    unsigned char reg_y;    // Register Y
    unsigned char ps;       // processor status
    cpu_8086_mem mem;
} cpu_8086;


// Function declarations for creating and destroying CPU 6502 instances, and resetting
cpu_8086 cpu_8086_create();
int cpu_8086_destroy(cpu_8086* cpu);
int cpu_8086_reset(cpu_8086* cpu);

void cpu_8086_print_state(cpu_8086* cpu, error* err);

//int cpu_8086_interpret_instruction_mov(parser_cst_node node, cpu_8086* cpu, error* err);
int cpu_8086_interpret_instruction(parser_cst_node node, cpu_8086* cpu, error* err);

lexer_token cpu_8086_lexer_next_token(char *input, int *line, int *pos, error* err);

#endif