#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"
#include "lexer.h"


#define MAX_CST_NODES 100
#define MAX_CST_NODE_CHILDREN 2

// concrete syntax tree (CST) token types
typedef enum {
    CST_UNKNOWN,
    CST_END_OF_INPUT,
    CST_NEWLINE,
    CST_INSTRUCTION,
    CST_REGISTER,
    CST_NUMBER,
    CST_IGNORE,
    CST_NUM_TYPES
} parser_cst_type;


// concrete syntax tree (CST) token struct
typedef struct  cst_node{
    parser_cst_type type;
    int line;
    int pos;
    char* value;
    struct cst_node* children;
    int num_children;
} parser_cst_node;


// const char* parser_map_cst_type_to_string(parser_cst_type t);
parser_cst_node parser_create_cst_node(error* err);
parser_cst_node parser_create_cst_node_values(int line, int pos, parser_cst_type type, char* value, error* err);
int parser_add_cst_node_to_cst_node(parser_cst_node* dst, parser_cst_node child, error* err);
parser_cst_node* parser_create_cst_node_arr(int size, error* err);
void parser_print_cst_node(parser_cst_node node);
void parser_print_cst_node_arr(parser_cst_node* cst_token_arr);
parser_cst_node* parser_process(lexer_token* cst_token_arr, int size, error* err);
parser_cst_node parser_next_token(lexer_token* input_arr, int i, error* err);
// parser_cst_node get_next_token(char *input, int *pos);


#endif