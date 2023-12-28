
#ifndef CPU_H
#define CPU_H


#define CPU_6502  1
#define CPU_8086  2
#define CPU_386   3
#define CPU_CURRENT  CPU_6502


#if CPU_CURRENT == CPU_6502
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_6502_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_6502_interpret_instruction(node, cpu, err)
#define cpu_current_parser_cst_node(input_arr, i, err)          cpu_6502_parser_cst_node(input_arr, i, err)

#elif CPU_CURRENT == CPU_8086
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_8086_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_8086_interpret_instruction(node, cpu, err)
#define cpu_current_parser_cst_node(input_arr, i, err)          cpu_8086_parser_cst_node(input_arr, i, err)

#elif CPU_CURRENT == CPU_386
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_386_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_386_interpret_instruction(node, cpu, err)
#define cpu_current_parser_cst_node(input_arr, i, err)          cpu_386_parser_cst_node(input_arr, i, err)

#else
#define cpu_current_lexer_next_token(input, line, pos, err)     cpu_unknown_lexer_next_token(input, line, pos, err)
#define cpu_current_interpret_instruction(node, cpu, err)       cpu_unknown_interpret_instruction(node, cpu, err)
#define cpu_current_parser_cst_node(input_arr, i, err)          cpu_unknown_parser_cst_node(input_arr, i, err)

#endif




typedef enum {
    CPU_TYPE_UNKNOWN,
    CPU_TYPE_6502,
    CPU_TYPE_8086,
    CPU_TYPE_386,
    CPU_NUM_TYPES
} cpu_type;


#endif