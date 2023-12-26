#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cerror.h"
#include "cheap.h"
#include "lexer.h"
#include "parser.h"
#include "ccharp.h"



// Function to map enum values to strings
const char* parser_map_cst_type_to_string(parser_cst_type t) {
    static const char* type_strings[CST_NUM_TYPES] = {
        "UNKNOWN",
        "END_OF_INPUT",
        "NEWLINE",
        "INSTRUCTION",
        "REGISTER",
        "NUMBER",
        "IGNORE"
    };

    if (t >= 0 && t < CST_NUM_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}


parser_cst_node parser_create_cst_node(error* err) {
    return parser_create_cst_node_values(0, 0, CST_UNKNOWN, "", err);
}

parser_cst_node parser_create_cst_node_values(int line, int pos, parser_cst_type type, char* value, error* err) {
    // TODO value verification missing: is_str(...)

    parser_cst_node node = {0};

    node.line = line;
    node.pos = pos;
    node.type = type;
    node.num_children = 0;


    size_t value_len = strlen(value) + 1;
    node.value = (char*) heap_calloc(value_len, sizeof(char), err);

    if (node.value == NULL) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocation memory", "unclear, probably a programming mistake or unsifficient memory.");
    }
    ccharp_copy_string(&node.value, value, err);

    return node;
}

int parser_add_cst_node_to_cst_node(parser_cst_node* dst, parser_cst_node child, error* err) {
    if (0 == dst->num_children ) {
        dst->   children = parser_create_cst_node_arr(2, err);
    }

    dst->children[dst->num_children] = child;
    dst->num_children++;
    
    return RET_SUCCESS;
}

parser_cst_node* parser_create_cst_node_arr(int size, error* err) {
    if (MAX_CST_NODES < size) {
        size = MAX_CST_NODES;
    } else if (0 == size) {
        size = 1;
    }

    parser_cst_node* ast_token_arr = heap_calloc(size, sizeof(parser_cst_node), err);  // Allocate memory for an array of structs

    if (NULL != ast_token_arr) {
        // Initialize the structs in the array (for demonstration, using dummy data)
        for (int i = 0; i < size; i++) {
            ast_token_arr[i] = parser_create_cst_node(err);
        }
    }

    return ast_token_arr;
}


// Function to print a cst_node
void parser_print_cst_node(parser_cst_node node) {
    printf("parser_cst_node: {type: %s (%d), line: %d, pos: %d, value: \"%s\"}\n", parser_map_cst_type_to_string(node.type), node.type, node.line, node.pos, node.value); 
    int i = 0;
    while (i < node.num_children) {
        printf("  -> ");
        parser_print_cst_node(node.children[i]);
        i++;
    }
}

void parser_print_cst_node_arr(parser_cst_node *cst_token_arr) {
    printf("#####################\n");
    int i = 0;
     while (MAX_TOKEN_NODES > i) {
        parser_print_cst_node(cst_token_arr[i]);
        
        if (CST_END_OF_INPUT == cst_token_arr[i].type) {
            break;
        }

        i++;
    }
    printf("#####################\n");
}


parser_cst_node* parser_process(lexer_token *lexer_token_arr, int size, error* err) {
    if (MAX_CST_NODES < size) {
        size = MAX_CST_NODES;
    } else if (0 == size) {
        size = 1;
    }

    parser_cst_node* cst_node_arr = parser_create_cst_node_arr(size, err);
    if (RET_ERR == error_check(*err) ) {
        return cst_node_arr;
    }
    parser_cst_node cst_node = parser_create_cst_node(err);
    if (RET_ERR == error_check(*err) ) {
        return cst_node_arr;
    }

    int i = 0;
    int instructions = 0;
    while (size > i) {
        //lexer_print_token(cst_token_arr[i]);
        cst_node = parser_next_token(lexer_token_arr, i, err);
        if (RET_ERR == error_check(*err) ) {
            break;
        }

        if (CST_INSTRUCTION == cst_node.type) {
            int found = 0;
            cst_node.children = parser_create_cst_node_arr(MAX_CST_NODE_CHILDREN, err);
            if (RET_ERR == error_check(*err) ) {
                break;
            }
            while (found < MAX_CST_NODE_CHILDREN) {
                parser_cst_node cst_node_child = parser_next_token(lexer_token_arr, ++i, err);
                if (RET_ERR == error_check(*err) ) {
                    break;
                }
                if (CST_IGNORE == cst_node_child.type) {
                    continue;
                }
                if (CST_END_OF_INPUT == cst_node_child.type || CST_UNKNOWN == cst_node_child.type) {
                    i--;
                    break;
                }
                
                cst_node.children[found] = cst_node_child;
                found++;
            }
            cst_node.num_children = found;
            

        } else if (CST_IGNORE == cst_node.type) {
            i++;
            continue;
        }

        cst_node_arr[instructions] = cst_node;
        instructions++;

        if (CST_END_OF_INPUT == cst_node.type) {
            break;
        }
        
        // cst_token_arr[i] = cst_node;TOKEN_END_OF_INPUT
        //parser_print_cst_node(cst_node);
        

        i++;
    }

    
    // parser_print_cst_node_arr(cst_node_arr);

    return cst_node_arr;
}


// Get the next token from input
parser_cst_node parser_next_token(lexer_token *input_arr, int i, error* err) {
    lexer_token input = input_arr[i];
    parser_cst_node token = parser_create_cst_node(err);
    if (RET_ERR == error_check(*err) ) {
        return token;
    }
    token.line = input.line;
    token.pos = input.pos;
    token.type = CST_UNKNOWN;

    // Check for unknown
    if (TOKEN_UNKNOWN == input.type ) {
        token.type = CST_UNKNOWN;
        token.value = input.value;
        return token;
    }

    // Check for end
    if (TOKEN_END_OF_INPUT == input.type ) {
        token.type = CST_END_OF_INPUT;
        return token;
    }

    // Check for newline
    if (TOKEN_NEWLINE == input.type) {
        token.type = CST_IGNORE;
        token.value = input.value;
        return token;
    } 

    // Check for Comma
    if (TOKEN_COMMA == input.type) {
        token.type = CST_IGNORE;
        strncpy(token.value, input.value, sizeof(token.value) - 1); // Copy at most sizeof(destination) - 1 characters
        token.value[sizeof(token.value) - 1] = '\0'; // Ensure null-termination
        return token;
    } 
    
    // Check for literal
    if (TOKEN_LITERAL == input.type ) {
        if (0 == token.pos) {
            token.type = CST_INSTRUCTION;
            strncpy(token.value, input.value, sizeof(token.value) - 1); // Copy at most sizeof(destination) - 1 characters
            token.value[sizeof(token.value) - 1] = '\0'; // Ensure null-termination

        } else {
            lexer_token *cst_token_current = &input_arr[i];
            lexer_token *cst_token_before = cst_token_current - 1; 

            if (TOKEN_NEWLINE == cst_token_before->type) {
                token.type = CST_INSTRUCTION;    
            } else {
                token.type = CST_REGISTER;
            }
            strncpy(token.value, input.value, sizeof(token.value) - 1); // Copy at most sizeof(destination) - 1 characters
            token.value[sizeof(token.value) - 1] = '\0'; // Ensure null-termination
        }
    
    // Check for deicmal number
    } else if (TOKEN_NUMBER_DEC == input.type ) {
        token.type = CST_NUMBER;
        strncpy(token.value, input.value, sizeof(token.value) - 1); // Copy at most sizeof(destination) - 1 characters
        token.value[sizeof(token.value) - 1] = '\0'; // Ensure null-termination

    // Check for hex number
    } else if (TOKEN_NUMBER_HEX == input.type ) {
        char* new_value = "";
        if (RET_ERR == ccharp_hex_string_to_int_charp(&new_value, input.value, err) ) {
            *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
        }

        token.type = CST_NUMBER;
        strncpy(token.value, new_value, sizeof(new_value) - 1); // Copy at most sizeof(destination) - 1 characters
        token.value[sizeof(token.value) - 1] = '\0'; // Ensure null-termination

        heap_free(new_value, err);

    }

    return token;
}




