#ifndef LEXER_H
#define LEXER_H


#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


#define MAX_TOKEN_NODES 100
#define MAX_TOKEN_VALUE 20


// lexer token types
typedef enum {
    TOKEN_UNKNOWN,
    TOKEN_END_OF_INPUT,
    TOKEN_NEWLINE,
    TOKEN_COMMA,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_NUM_TYPES
} lexer_token_type;

// lexer token struct
typedef struct {
    lexer_token_type type;
    int line;
    int pos;
    char* value;
} lexer_token;


// const char* lexer_map_token_type_to_string(lexer_token_type t);
lexer_token lexer_create_token(error* err);
lexer_token lexer_create_token_values(int line, int pos, lexer_token_type type, char* value, error* err);
lexer_token* lexer_create_token_arr(int size, error* err);
void lexer_print_token(lexer_token node);
void lexer_print_token_arr(lexer_token* node_arr);
lexer_token* lexer_process_string(char* input, error* err);
lexer_token lexer_next_token(char* input, int* pos, int* line, error* err);


#endif