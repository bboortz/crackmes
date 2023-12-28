#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerror.h"
#include "opcode.h"
#include "ccharp.h"
#include "cheap.h"


opcode_instruction opcode_instructions[] = {
    {OPCODE_LDA, ADDRESSING_IMMEDIATE, 0xA9, 2},
    {OPCODE_LDA, ADDRESSING_ZERO_PAGE, 0x85, 2},
    // Add more instructions here
};



// Function to map enum values to strings
const char* opcode_map_mnemonic_to_string(opcode_mnemonic t) {
    static const char* type_strings[TOKEN_NUM_INSTRUCTION_TYPES] = {
        "UNKNOWN",
        "LDA",
        "LDX",
        "LDY",
        "STA",
        "STX",
        "STY",
        "PHA",
        "PHX",
        "PHY",
        "PLA",
        "PLX",
        "PLY",
    };

    if (t >= 0 && t < TOKEN_NUM_INSTRUCTION_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}


// Function to map enum values to strings
const char* opcode_map_addressing_mode_to_string(opcode_addressing_mode t) {
    static const char* type_strings[TOKEN_NUM_ADDRESSING_MODES] = {
        "UNKNOWN",
        "ACCUMULATOR",
        "ADDRESSING_IMMEDIATE",
        "ZERO_PAGE",
        "ZERO_PAGE_X",
        "ZERO_PAGE_Y",
        "RELATIVE",
        "ABSOLUTE",
        "ABSOLUTE_X",
        "ABSOLUTE_Y",
        "INDIRECT",
        "INDIRECT_ZERO_PAGE",
        "INDEXED_INDIRECT",
        "INDIRECT_INDEXED",
        "ABSOLUTE_INDEXED_INDIRECT",
    };

    if (t >= 0 && t < TOKEN_NUM_ADDRESSING_MODES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}


// Function to print a lexer_token
void opcode_print_instruction(opcode_instruction inst) {
    printf("instruction: {mnemonic: %s (%d), addressing_mode: %s (%d), opcode: %d, length: %d }\n",  opcode_map_mnemonic_to_string(inst.mnemonic), inst.mnemonic, opcode_map_addressing_mode_to_string(inst.mode), inst.mode, inst.opcode, inst.length); 
}



/*
int opcode_destroy_instruction(opcode_instruction *inst, error *err) {
    if (NULL == inst) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "instruction empty", "instruction is null.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    return heap_free( (void*)inst->mnemonic, err);
}
*/


opcode_instruction opcode_create_instruction(opcode_mnemonic mnemonic, opcode_addressing_mode mode, uint8_t opcode, uint8_t length, error *err) {
    opcode_instruction instruction = {mnemonic, opcode, mode, length};
    instruction.mnemonic = mnemonic;
    instruction.mode = mode;
    instruction.opcode = opcode;
    instruction.length = length;

    if (OPCODE_UNKNOWN == mnemonic) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Mnemonic is unknown", "Mnemonic unknown!");
    }

    if (NULL == err) {
        *err = error_create_default();
    }
    
    return instruction;
}



opcode_instruction opcode_get_instruction(opcode_mnemonic mnemonic, opcode_addressing_mode mode, error* err) {
    size_t instruction_num = sizeof(opcode_instructions) / sizeof(opcode_instructions[0]);

    for (int i = 0; i < (int) instruction_num; ++i) {
        if (opcode_instructions[i].mode == mode) {
            if (opcode_instructions[i].mnemonic == mnemonic) {
                return opcode_instructions[i];
            }
        }
    }
    // Return 0 if the instruction is not found
    return opcode_create_instruction(OPCODE_UNKNOWN, ADDRESSING_UNKNOWN, 0, 0, err);
}
