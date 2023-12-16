#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


// Function to map enum values to strings
const char* lexer_map_token_type_to_string(lexer_token_type t) {
    static const char* type_strings[TOKEN_NUM_TYPES] = {
        "UNKNOWN",
        "END_OF_INPUT",
        "NEWLINE",
        "COMMA(,)",
        "STRING",
        "NUMBER",
        
    };

    if (t >= 0 && t < TOKEN_NUM_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}


lexer_token lexer_create_token(void) {
    lexer_token cst_token = {0};

    cst_token.line = 0;
    cst_token.pos = 0;
    cst_token.type = TOKEN_UNKNOWN;
    cst_token.value[0] = '\n';
    
    return cst_token;
}

lexer_token* lexer_create_token_arr(int size) {
    if (MAX_TOKEN_NODES < size) {
        size = MAX_TOKEN_NODES;
    } else if (0 == size) {
        size = 1;
    }
    lexer_token* cst_token_arr = malloc(size * sizeof(lexer_token)); // Allocate memory for an array of structs

    if (NULL != cst_token_arr) {
        // Initialize the structs in the array (for demonstration, using dummy data)
        for (int i = 0; i < size; i++) {
            cst_token_arr[i] = lexer_create_token();
        }
    }

    return cst_token_arr;
}


// Function to print a lexer_token
void lexer_print_token(lexer_token node) {
    printf("lexer_token: {type: %s (%d), line: %d, pos: %d, value: \"%s\"}\n", lexer_map_token_type_to_string(node.type), node.type, node.line, node.pos, node.value); 
}


lexer_token* lexer_process_string(char *input) {
    int line = 0;
    int pos = 0;
    
    lexer_token* cst_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES);


    int i = 0;
    while (MAX_TOKEN_NODES > i) {
        cst_token_arr[i] = lexer_next_token(input, &pos, &line);
        // lexer_print_token(cst_token_arr[i]);
        
        if (TOKEN_END_OF_INPUT == cst_token_arr[i].type) {
            break;
        }

        i++;
    }

    return cst_token_arr;
}

// Get the next token from input
lexer_token lexer_next_token(char *input, int *line, int *pos) {
    lexer_token token = {0};
    int l = *line;
    int p = *pos;
    int length = strlen(input);
    // token.type = TOKEN_UNKNOWN;
    token.line = l;
    token.pos = p;
    //memset(token.value, 0, strlen(token.value));


    // Check for newline
    if ('\n' == input[p] ) {
        token.type = TOKEN_NEWLINE;
        token.line++;
        l++;
        p++;
        *line = l;
        *pos = p;
        return token;
    }

    // Skip whitespace
    while (p < length && isspace(input[p])) {
        token.pos++;
        p++;
    }

    // Check for end of input
    if (p == length) {
        token.type = TOKEN_END_OF_INPUT;
        *pos = p;
        return token;
    }

    // Check for comma (,)
    else if (',' == input[p]) {
        token.value[0] = input[p++];
        token.value[1] = '\0';
        token.type = TOKEN_COMMA;
    }
    
    // Check for strings
    else if (isalpha(input[p])) {
        int j = 0;
        while (j < MAX_TOKEN_VALUE && p < length && isalpha(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_STRING;
    }

    // Check for numerical operands
    else if (isdigit(input[p])) {
        int j = 0;
        while (j < MAX_TOKEN_VALUE && p < length && isdigit(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_NUMBER;
    } else {
        token.type = TOKEN_UNKNOWN;
        token.value[0] = input[p];
        token.value[1] = '\0';
        p++;
    }

    *pos = p;
    *line = l;
    
    return token;
}



