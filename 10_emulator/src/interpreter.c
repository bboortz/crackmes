#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"
#include "parser.h"
#include "ccharp.h"


interpreter_state interpreter_create_state() {
    interpreter_state state = {0};

    state.ip = 0;
    state.reg_a = 0;
    state.err = error_create_default();

    return state;
}


int interpreter_interpret_instruction_mov(parser_cst_node node, interpreter_state* state, error* err) {
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
    state->reg_a = number; // atoi(node.children[2].value);

    return RET_SUCCESS;
}



int interpreter_interpret_instruction(parser_cst_node node, interpreter_state* state, error* err) {
    parser_print_cst_node(node);
    error_print(*err);

    printf("Instruction: %s\n", node.value);
    if (strncmp(node.value, "MOV", strlen("option1")) == 0) {
        printf("MOV instruction\n");
        interpreter_interpret_instruction_mov(node, state, err);
    } else {
        char *err_msg = "";
        char *str1 = "unknown instruction";
        if (RET_ERR == error_create_message(&err_msg, str1, node.value, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "character instruction. please verify your input.");
        return RET_ERR;
    }

    return RET_SUCCESS;
}

int interpreter_interpret_cst_node(parser_cst_node node, interpreter_state* state, error* err) {

    printf("------------\n");
    parser_print_cst_node(node);
    error_print(*err);
    printf("------------\n");
    switch (node.type) {
        case CST_INSTRUCTION:
            interpreter_interpret_instruction(node, state, err);
            break;
        case CST_END_OF_INPUT:
            printf("End of input\n");
            break;
        case CST_UNKNOWN:
            printf("Unknown token\n");
            break;
        default:
            printf("completely Unknown token\n");
            break;

    }

    state->ip++;

    printf("\n *** ip: %d - reg_a: %d\n", state->ip, state->reg_a);

    return RET_SUCCESS;
}