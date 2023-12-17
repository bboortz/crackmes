#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
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


lexer_token lexer_create_token(error *err) {
    return lexer_create_token_values(0, 0, TOKEN_UNKNOWN, "", err);
}

lexer_token lexer_create_token_values(int line, int pos, lexer_token_type type, char* value, error *err) {
    lexer_token token = {line, pos, type, value};

    token.line = line;
    token.pos = pos;
    token.type = type;

    token.value = (char *)malloc((strlen(value) + 1) * sizeof(char));

    if (token.value == NULL) {
        *err = util_create_error(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocation memory", "unclear, probably a programming mistake or unsifficient memory.");
    }
    util_copy_string(&token.value, value);
    
    return token;
}

lexer_token* lexer_create_token_arr(int size, error* err) {
    if (MAX_TOKEN_NODES < size) {
        size = MAX_TOKEN_NODES;
    } else if (0 == size) {
        size = 1;
    }

    lexer_token* cst_token_arr = malloc(size * sizeof(lexer_token)); // Allocate memory for an array of structs

    if (NULL != cst_token_arr) {
    }
        
    for (int i = 0; i < size; i++) {
        cst_token_arr[i] = lexer_create_token(err);

        if (RET_ERR == util_check_error(*err) ) {
            break;
        }
    }

    return cst_token_arr;
}


// Function to print a lexer_token
void lexer_print_token(lexer_token node) {
    printf("lexer_token: {type: %s (%d), line: %d, pos: %d, value: \"%s\"}\n", lexer_map_token_type_to_string(node.type), node.type, node.line, node.pos, node.value); 
}

void lexer_print_token_arr(lexer_token* node_arr) {
    printf("#####################\n");
    int i = 0;
     while (MAX_TOKEN_NODES > i) {
        lexer_print_token(node_arr[i]);
        
        if (TOKEN_END_OF_INPUT == node_arr[i].type) {
            break;
        }

        i++;
    }
    printf("#####################\n");

}


lexer_token* lexer_process_string(char *input, error *err) {
    int line = 0;
    int pos = 0;
    
    lexer_token* cst_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES, err);
    if (RET_ERR == util_check_error(*err) ) {
        return cst_token_arr;
    }

    int i = 0;
    while (MAX_TOKEN_NODES > i) {
        // *err = util_create_error_default();
        cst_token_arr[i] = lexer_next_token(input, &pos, &line, err);
        // lexer_print_token(cst_token_arr[i]);
        // util_print_error(*err);
        if (RET_ERR == util_check_error(*err) ) {
            break;
        }
        
        if (TOKEN_END_OF_INPUT == cst_token_arr[i].type) {
            break;
        }

        i++;
    }

    return cst_token_arr;
}

// Get the next token from input
lexer_token lexer_next_token(char *input, int *line, int *pos, error* err) {
    lexer_token token = lexer_create_token(err);

    int l = *line;
    int p = *pos;
    size_t length = strlen(input);
    token.line = l;
    token.pos = p;

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
    while (p < (int) length && isspace(input[p])) {
        token.pos++;
        p++;
    }

    // Check for end of input
    if (p == (int) length) {
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
        // TODO replace copy method!
        char* token_str = "";
        
        while (p < (int) length && isalpha(input[p])) {
            if (j >= MAX_TOKEN_VALUE) {
                *err = util_create_error(ERR_BOUNDARY, ERR_CRIT_ERROR, "too much input", "more input that internal data structure can handle.");
                if (RET_ERR == util_check_error(*err) ) {
                   break;
                }
            }
            // TODO replace char to string method
            char char_string[2]; // Reserve space for character + null terminator
            char_string[0] = input[p];
            char_string[1] = '\0';
            util_concat_strings(&token_str, token_str, char_string);
            //token.value[j++] = input[p++];
            j++;
            p++;
        }
        // token.value[j] = '\0';
        token.value = token_str;
        token.type = TOKEN_STRING;
    }

    // Check for numerical operands
    else if (isdigit(input[p])) {
        int j = 0;
        // TODO replace copy method!
        while (j < MAX_TOKEN_VALUE && p < (int) length && isdigit(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_NUMBER;
    } else {
        token.type = TOKEN_UNKNOWN;
        token.value[0] = input[p];
        token.value[1] = '\0';
        
        char *err_msg = "";
        char *str1 = "unknown character";
        if (RET_ERR == util_create_error_message(&err_msg, str1, token.value) ) {
            *err = util_create_error(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        
        *err = util_create_error(ERR_LEXER, ERR_CRIT_WARN, err_msg, "character unknown. please verify your input.");
        // util_print_error(*err);
        /* TODO think about it, if we are returning directly here or later
        if (RET_ERR == util_check_error(*err) ) {
            return 
        }
        */
        p++;
    }

    *pos = p;
    *line = l;
    
    return token;
}



