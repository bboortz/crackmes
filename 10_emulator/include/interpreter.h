#ifndef INTERPRETER_H
#define INTERPRETER_H



#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "cerror.h"


// concrete syntax tree (CST) token struct
typedef struct {
    parser_cst_type type;
    int ip;
    int reg_a;
    error err;
} interpreter_state;


interpreter_state interpreter_create_state();
int interpreter_interpret_cst_node(parser_cst_node node, interpreter_state* state, error* err);


#endif