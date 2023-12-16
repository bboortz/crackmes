#ifndef LEXER_H
#define LEXER_H


#include <stdio.h>
#include <stdlib.h>


#define MAX_TOKEN_NODES 100


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
    char value[20];
} lexer_token;


const char* lexer_map_token_type_to_string(lexer_token_type t);
lexer_token lexer_create_token();
lexer_token* lexer_create_token_arr(int size);
void lexer_print_token(lexer_token node);
lexer_token* lexer_process_string(char *input);
lexer_token lexer_next_token(char *input, int *pos, int *line);


#endif