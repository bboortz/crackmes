
#ifndef CPU_H
#define CPU_H


#include <stdint.h>



#define CPU_6502  1
#define CPU_8086  2
#define CPU_386   3
#define CPU_CURRENT  CPU_6502


typedef enum {
    CPU_TYPE_UNKNOWN,
    CPU_TYPE_6502,
    CPU_TYPE_8086,
    CPU_TYPE_386,
    CPU_NUM_TYPES
} cpu_type;




typedef enum {
    CPU_6502_INSTRUCTION_UNKNOWN,
    CPU_6502_INSTRUCTION_NOP,
    CPU_6502_INSTRUCTION_LDA,
    CPU_6502_INSTRUCTION_LDX,
    CPU_6502_INSTRUCTION_LDY,
    CPU_6502_INSTRUCTION_STA,
    CPU_6502_INSTRUCTION_STX,
    CPU_6502_INSTRUCTION_STY,
    CPU_6502_INSTRUCTION_PHA,
    CPU_6502_INSTRUCTION_PHP,
    CPU_6502_INSTRUCTION_PLA,
    CPU_6502_INSTRUCTION_PLP,
    CPU_6502_NUM_INSTRUCTION
} cpu_6502_instruction_mnemonic;


typedef enum {
    CPU_6502_ADDRESSING_UNKNOWN,
    CPU_6502_ADDRESSING_IMPLICIT,
    CPU_6502_ADDRESSING_ACCUMULATOR,
    CPU_6502_ADDRESSING_IMMEDIATE,
    CPU_6502_ADDRESSING_ZERO_PAGE,
    CPU_6502_ADDRESSING_ZERO_PAGE_X,
    CPU_6502_ADDRESSING_ZERO_PAGE_Y,
    CPU_6502_ADDRESSING_RELATIVE,
    CPU_6502_ADDRESSING_ABSOLUTE,
    CPU_6502_ADDRESSING_ABSOLUTE_X,
    CPU_6502_ADDRESSING_ABSOLUTE_Y,
    CPU_6502_ADDRESSING_INDIRECT,
    CPU_6502_ADDRESSING_INDIRECT_ZERO_PAGE,
    CPU_6502_ADDRESSING_INDEXED_INDIRECT,
    CPU_6502_ADDRESSING_INDIRECT_INDEXED,
    CPU_6502_ADDRESSING_ABSOLUTE_INDEXED_INDIRECT,
    CPU_6502_NUM_ADDRESSING
} cpu_6502_addressing_mode;


typedef struct {
    cpu_6502_instruction_mnemonic mnemonic;
    cpu_6502_addressing_mode mode;
    uint8_t opcode;
    uint8_t length;
} cpu_6502_instruction;


//extern cpu_6502_instruction instructions_array[];


#if CPU_CURRENT == CPU_6502
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_6502_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_6502_interpret_instruction(node, cpu, err)
#define cpu_current_parser_next_token(input_arr, i, err)        cpu_6502_parser_next_token(input_arr, i, err)
#define cpu_current_instruction                                 cpu_6502_instruction
#define cpu_current_instruction_mnemonic                            cpu_6502_instruction_mnemonic
#define cpu_current_addressing_mode                             cpu_6502_addressing_mode
#define cpu_current_map_mnemonic_to_string                      cpu_6502_map_mnemonic_to_string
#define cpu_current_map_addressing_mode_to_string               cpu_6502_map_addressing_mode_to_string

#elif CPU_CURRENT == CPU_8086
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_8086_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_8086_interpret_instruction(node, cpu, err)
#define cpu_current_parser_next_token(input_arr, i, err)        cpu_8086_parser_next_token(input_arr, i, err)
#define cpu_current_instruction                                 cpu_8086_instruction
#define cpu_current_instruction_mnemonic                            cpu_8086_instruction_mnemonic
#define cpu_current_addressing_mode                             cpu_8086_addressing_mode
#define cpu_current_map_mnemonic_to_string                      cpu_8086_map_mnemonic_to_string
#define cpu_current_map_addressing_mode_to_string               cpu_8086_map_addressing_mode_to_string

#elif CPU_CURRENT == CPU_386
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_386_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_386_interpret_instruction(node, cpu, err)
#define cpu_current_parser_next_token(input_arr, i, err)        cpu_386_parser_next_token(input_arr, i, err)
#define cpu_current_instruction                                 cpu_386_instruction
#define cpu_current_instruction_mnemonic                            cpu_386_instruction_mnemonic
#define cpu_current_addressing_mode                             cpu_386_addressing_mode
#define cpu_current_map_mnemonic_to_string                      cpu_386_map_mnemonic_to_string
#define cpu_current_map_addressing_mode_to_string               cpu_386_map_addressing_mode_to_string

#else
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_unknown_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_unknown_interpret_instruction(node, cpu, err)
#define cpu_current_parser_next_token(input_arr, i, err)        cpu_unknown_parser_next_token(input_arr, i, err)
#define cpu_current_instruction                                 cpu_unknown_instruction
#define cpu_current_instruction_mnemonic                            cpu_unknown_instruction_mnemonic
#define cpu_current_addressing_mode                             cpu_unknown_addressing_mode
#define cpu_current_map_mnemonic_to_string                      cpu_unknown_map_mnemonic_to_string
#define cpu_current_map_addressing_mode_to_string               cpu_unknown_map_addressing_mode_to_string

#endif




#endif
