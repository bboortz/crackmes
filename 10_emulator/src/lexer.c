#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "cerror.h"
#include "cheap.h"
#include "ccharp.h"
#include "cpu.h"
#include "cpu_6502.h"



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
        //printf("i %d\n", i);
        //void* ptr = &token_arr[i];
        //printf("lalala: %d - %d - %p\n", i, MAX_TOKEN_NODES, ptr );
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

    //printf("lalala+: %d\n", size);
    lexer_token* cst_token_arr = heap_calloc(size, sizeof(lexer_token), err);
    //printf("lalala\n");
    //lexer_token* cst_token_arr = util_malloc(size * sizeof(lexer_token), err); // Allocate memory for an array of structs

    if (NULL != cst_token_arr) {
    }
        
    for (int i = 0; i < size && i < MAX_TOKEN_NODES; i++) {
        //void* ptr = &cst_token_arr[i];
        //printf("lalala: %d - %d - %p\n", i, size, ptr );
        cst_token_arr[i] = lexer_create_token(err);
        //error_print(*err);
        //printf("alalala: %d - %d\n", i, size);
        if (NULL != err && RET_ERR == error_check(*err) ) {
            //printf("BOOOOOM: %d - %d\n", i, size);
            continue;
        }
        //error_destroy(err);
        //printf("yes: %d - %d\n", i, size);
    }

    return cst_token_arr;
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


    //printf("########### before ########>>>>>\n");
    int i = 0;
    while (MAX_TOKEN_NODES > i) {
        //printf("########### %d ########>>>>>\n", i);
        //error_print(*err);
        e = error_create_default();
        if (0 == i) {
            *err = e;
        }
        cst_token_arr[i] = cpu_current_lexer_next_token(input, &pos, &line, &e);
        //lexer_print_token(cst_token_arr[i]);
        //printf("-------------->>\n");
        //error_print(e);
        //printf("--------------\n");
        if (e.code != ERR_SUCCESS) {
            //printf("-------------- err\n");
            *err = e;
            //error_print(*err);
            i++;
            continue;

        } 
        
        if (RET_ERR == error_check(e) ) {
            //printf("-------------- break\n");
            error_destroy(&e);
            break;
        }
        //printf("--------------\n");
        
        if (TOKEN_END_OF_INPUT == cst_token_arr[i].type) {
            error_destroy(&e);
            break;
        }

        i++;
        //printf("<<--------------\n");
        
        //error_destroy(&e);
    }

    //printf("<<<<<<<########### %d ########\n", i);
    //error_print(*err);

    return cst_token_arr;
}



