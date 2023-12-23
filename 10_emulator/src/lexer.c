#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "cerror.h"
#include "cheap.h"
#include "ccharp.h"
//#include "cstring.h"



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



// Function to print a lexer_token
void lexer_print_token(lexer_token node) {
    printf("lexer_token: {type: %s (%d), line: %d, pos: %d, value: \"%s\"}\n", lexer_map_token_type_to_string(node.type), node.type, node.line, node.pos, node.value); 
}


void lexer_print_token_arr(lexer_token* node_arr) {
    printf("#####################\n");

    for(int i = 0; i < MAX_TOKEN_NODES; i++) {
        lexer_print_token(node_arr[i]);
        
        if (TOKEN_END_OF_INPUT == node_arr[i].type) {
            break;
        }
    }
    printf("#####################\n");

}



int lexer_destroy_token(lexer_token *token, error *err) {
    if (NULL == token) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "token empty", "token is null.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }
    
    // heap_free(exp_token.value), &err);
    //return heap_free( (void*)token->value, err);
    return heap_free( (void*)token->value, err);
}


lexer_token lexer_create_token(error *err) {
    return lexer_create_token_values(0, 0, TOKEN_UNKNOWN, "", err);
}


lexer_token lexer_create_token_values(int line, int pos, lexer_token_type type, char* value, error *err) {
    lexer_token token = {line, pos, type, value};

    token.line = line;
    token.pos = pos;
    token.type = type;

    //size_t value_len = strlen(value) + 1;
    //token.value = (char*) heap_calloc(value_len, sizeof(char), err);

    if (NULL == token.value) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocation memory", "unclear, probably a programming mistake or unsifficient memory.");
    }

    ccharp_copy_string(&token.value, value, err);


    if (NULL == err) {
        *err = error_create_default();
    }
    
    //string_copy_charp(&token.value, value, err);
    
    return token;
}


int lexer_destroy_token_arr(lexer_token* token_arr, error *err) {
    if (NULL == token_arr) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "token array empty", "array is null.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }
        
    for(int i = 0; i < MAX_TOKEN_NODES; i++) {
        printf("i %d\n", i);
        void* ptr = &token_arr[i];
        printf("lalala: %d - %d - %p\n", i, MAX_TOKEN_NODES, ptr );
        // heap_free( (void*)token_arr[i]->value, err);
        lexer_print_token(token_arr[i]);
        lexer_destroy_token(&token_arr[i], err);
    }
    

    return heap_free( (void*)token_arr, err);

}


lexer_token* lexer_create_token_arr(int size, error* err) {
    if (MAX_TOKEN_NODES < size) {
        size = MAX_TOKEN_NODES;
    } else if (0 == size) {
        size = 1;
    }

    printf("lalala+: %d\n", size);
    lexer_token* cst_token_arr = heap_calloc(size, sizeof(lexer_token), err);
    printf("lalala\n");
    //lexer_token* cst_token_arr = util_malloc(size * sizeof(lexer_token), err); // Allocate memory for an array of structs

    if (NULL != cst_token_arr) {
    }
        
    for (int i = 0; i < size && i < MAX_TOKEN_NODES; i++) {
        void* ptr = &cst_token_arr[i];
        printf("lalala: %d - %d - %p\n", i, size, ptr );
        cst_token_arr[i] = lexer_create_token(err);
        //error_print(*err);
        //printf("alalala: %d - %d\n", i, size);
        if (NULL != err && RET_ERR == error_check(*err) ) {
            printf("BOOOOOM: %d - %d\n", i, size);
            continue;
        }
        //error_destroy(err);
        printf("yes: %d - %d\n", i, size);
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


    printf("# %d - %ld - <%s>\n", p, length, input);

    // Check for newline
    if ('\n' == input[p] ) {
        printf("newline\n");
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        l++;
        token.type = TOKEN_NEWLINE;
        *err = error_create_default();

        *line = l;
        *pos = p;
        return token;

    /*
        token.type = TOKEN_NEWLINE;
        token.line++;
        l++;
        p++;
        *line = l;
        *pos = p;
        return token;
        */  
    }

    // Skip whitespace
    while (p < (int) length && isspace(input[p])) {
        printf("white\n");
        token.pos++;
        p++;
    }

    printf("# %d - %ld - <%s>\n", p, length, input);

    // Check for end of input
    if (p == (int) length) {
        printf("end......\n");
        token.type = TOKEN_END_OF_INPUT;
        *err = error_create_default();
        //*pos = p;
        //return token;  
    
    // Check for comma (,)
    } else if (',' == input[p]) {
        printf("-# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        token.type = TOKEN_COMMA;
        printf("-# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        *err = error_create_default();
/*
        token.value[0] = input[p++];
        token.value[1] = '\0';
        token.type = TOKEN_COMMA;
        *err = error_create_default();
        */
    
    // Check for strings
    } else if (isalpha(input[p])) {
        printf("## %d\n", *pos);

        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring_as_long_as_char(&token.value, input, err);
        token.type = TOKEN_STRING;
        *err = error_create_default();

/*
        int j = 0;
        // TODO replace copy method!
        //char* token_str = (char*) heap_calloc(1, sizeof(char), err);
        //char token_str[MAX_TOKEN_VALUE];
        //if (NULL == token_str) {
        //    *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
        //}
        
        
        while (p < (int) length && isalpha(input[p])) {
            if (j >= MAX_TOKEN_VALUE) {
                *err = error_create(ERR_BOUNDARY, ERR_CRIT_ERROR, "too much input", "more input that internal data structure can handle.");
                if (RET_ERR == error_check(*err) ) {
                   break;
                }
            }
            // TODO replace char to string method
            
            //char char_string[2]; // Reserve space for character + null terminator
            //char_string[0] = input[p];
            //char_string[1] = '\0';
            //util_concat_strings(&token_str, token_str, char_string, err);
            //j++;
            //p++;
            token.value[j++] = input[p++];
            
        }
        token.value[j] = '\0';

        // token.value = token_str;
        //heap_free(token_str, err);
        */
        //p += 2;
        // l += p;
        //*pos = p;
        
        //token.type = TOKEN_STRING;
        


    // Check for numerical operands
    } else if (isdigit(input[p])) {
        printf("## %d\n", *pos);

        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring_as_long_as_digit(&token.value, input, err);
        token.type = TOKEN_NUMBER;
        *err = error_create_default();

        /*
        int j = 0;
        // TODO replace copy method!
        while (j < MAX_TOKEN_VALUE && p < (int) length && isdigit(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_NUMBER;
        */

    // unknown
    } else {
        printf("# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        token.type = TOKEN_UNKNOWN;
        printf("# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        char *err_msg;
        char *str1 = "unknown character";
        if (RET_ERR == error_create_message(&err_msg, str1, token.value, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_WARN, err_msg, "character unknown. please verify your input.");
        heap_free(err_msg, err);
        //heap_free(err_msg, err);
        // util_print_error(*err);
        /* TODO think about it, if we are returning directly here or later
        if (RET_ERR == error_check(*err) ) {
            return 
        }
        */

    }

    *pos = p;
    *line = l;
    
    return token;
}



lexer_token* lexer_process_string(char *input, error *err) {
    int line = 0;
    int pos = 0;
    
    error e = error_create_default();
    lexer_token* cst_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES, &e);
    if (RET_ERR == error_check(e) ) {
        return cst_token_arr;
    }
    error_destroy(&e);


    printf("########### before ########>>>>>\n");
    int i = 0;
    while (MAX_TOKEN_NODES > i) {
        printf("########### %d ########>>>>>\n", i);
        error_print(*err);
        e = error_create_default();
        if (0 == i) {
            *err = e;
        }
        cst_token_arr[i] = lexer_next_token(input, &pos, &line, &e);
        //lexer_print_token(cst_token_arr[i]);
        printf("-------------->>\n");
        error_print(e);
        printf("--------------\n");
        if (e.code != ERR_SUCCESS) {
            printf("-------------- err\n");
            *err = e;
            error_print(*err);
            i++;
            continue;

        } 
        
        if (RET_ERR == error_check(e) ) {
            printf("-------------- break\n");
            error_destroy(&e);
            break;
        }
        printf("--------------\n");
        
        if (TOKEN_END_OF_INPUT == cst_token_arr[i].type) {
            error_destroy(&e);
            break;
        }

        i++;
        printf("<<--------------\n");
        
        //error_destroy(&e);
    }

    printf("<<<<<<<########### %d ########\n", i);
    error_print(*err);

    return cst_token_arr;
}



