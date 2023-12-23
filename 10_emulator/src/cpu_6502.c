#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "parser.h"
#include "ccharp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cpu_6502.h"



cpu_6502 cpu_6502_create() {
    cpu_6502 cpu = {0};

    cpu_6502_reset(&cpu);

    return cpu;
}


int cpu_6502_destroy(cpu_6502* cpu) {
    return cpu_6502_reset(cpu);
}

int cpu_6502_reset(cpu_6502* cpu) {
    cpu->ip = 0xFFFC;
    cpu->sp = 0x0100;
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->reg_y = 0;

    return RET_SUCCESS;
}



int cpu_6502_interpret_instruction_mov(parser_cst_node node, cpu_6502* cpu, error* err) {
    parser_print_cst_node(node);
    error_print(*err);

    if (2 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction MOV needs 2 parameter", "wrong number of parameters.");
    }

    int number = 0;
    printf("-> %s\n", node.children[1].value);
    // if (RET_ERR == ccharp_string_to_int(&number, "3") ) {
    if (RET_ERR == ccharp_string_to_int(&number, node.children[1].value) ) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
    }
    cpu->reg_a = number; // atoi(node.children[2].value);

    return RET_SUCCESS;
}



int cpu_6502_interpret_instruction(parser_cst_node node, cpu_6502* cpu, error* err) {
    parser_print_cst_node(node);
    error_print(*err);
    
    ccharp_toupper_string(node.value);
    char *instruction = node.value;
    size_t instruction_len = strlen(instruction);

    printf("Instruction: %s\n", instruction);
    if (strncmp(instruction, "MOV", instruction_len) == 0) {
        printf("MOV instruction\n");
        cpu_6502_interpret_instruction_mov(node, cpu, err);
    } else {
        char *err_msg = "";
        char *str1 = "unknown instruction";
        if (RET_ERR == error_create_message(&err_msg, str1, instruction, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "character instruction. please verify your input.");
        return RET_ERR;
    }

    return RET_SUCCESS;
}