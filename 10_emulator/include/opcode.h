#ifndef OPCODE_H
#define OPCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cerror.h"


typedef enum {
    OPCODE_UNKNOWN,
    OPCODE_LDA,
    OPCODE_LDX,
    OPCODE_LDY,
    OPCODE_STA,
    OPCODE_STX,
    OPCODE_STY,
    OPCODE_PHA,
    OPCODE_PHX,
    OPCODE_PHY,
    OPCODE_PLA,
    OPCODE_PLX,
    OPCODE_PLY,
    TOKEN_NUM_INSTRUCTION_TYPES
} opcode_mnemonic;

typedef enum {
    ADDRESSING_UNKNOWN,
    ADDRESSING_ACCUMULATOR,
    ADDRESSING_IMMEDIATE,
    ADDRESSING_ZERO_PAGE,
    ADDRESSING_ZERO_PAGE_X,
    ADDRESSING_ZERO_PAGE_Y,
    ADDRESSING_RELATIVE,
    ADDRESSING_ABSOLUTE,
    ADDRESSING_ABSOLUTE_X,
    ADDRESSING_ABSOLUTE_Y,
    ADDRESSING_INDIRECT,
    ADDRESSING_INDIRECT_ZERO_PAGE,
    ADDRESSING_INDEXED_INDIRECT,
    ADDRESSING_INDIRECT_INDEXED,
    ADDRESSING_ABSOLUTE_INDEXED_INDIRECT,
    TOKEN_NUM_ADDRESSING_MODES
} opcode_addressing_mode;


typedef struct {
    opcode_mnemonic mnemonic;
    opcode_addressing_mode mode;
    uint8_t opcode;
    uint8_t length;
} opcode_instruction;


const char* opcode_map_mnemonic_to_string(opcode_mnemonic t);
const char* opcode_map_addressing_mode_to_string(opcode_addressing_mode t);

void opcode_print_instruction(opcode_instruction inst);

// int opcode_destroy_instruction(opcode_instruction *inst, error *err);
opcode_instruction opcode_create_instruction(opcode_mnemonic mnemonic, opcode_addressing_mode mode, uint8_t opcode, uint8_t length, error *err);

opcode_instruction opcode_get_instruction(opcode_mnemonic mnemonic, opcode_addressing_mode mode, error* err);



#endif