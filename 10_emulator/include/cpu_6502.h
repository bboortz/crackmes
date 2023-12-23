#ifndef CPU_6502_H
#define CPU_6502_H

#include "parser.h"


// Define a constant representing the maximum memory size for the CPU 6502
#define CPU_6502_MAX_MEM 1024 * 64


// Define a struct representing the memory of CPU 6502
typedef struct {
    unsigned char data[CPU_6502_MAX_MEM];  // Array to hold CPU memory data
} cpu_6502_mem;


// Define a struct representing CPU 6502
typedef struct {
    uint16_t ip;            // Instruction pointer = program counter
    uint16_t sp;            // Stack pointer
    unsigned char reg_a;    // Register A
    unsigned char reg_x;    // Register X
    unsigned char reg_y;    // Register Y
} cpu_6502;


// Function declarations for creating and destroying CPU 6502 instances, and resetting
cpu_6502 cpu_6502_create();
int cpu_6502_destroy(cpu_6502* cpu);
int cpu_6502_reset(cpu_6502* cpu);

int cpu_6502_interpret_instruction_mov(parser_cst_node node, cpu_6502* cpu, error* err);
int cpu_6502_interpret_instruction(parser_cst_node node, cpu_6502* cpu, error* err);

#endif