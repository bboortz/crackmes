#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "scanner.h"
#include "lexer.h"
#include "parser.h"



// Function to print a scanner_token
void scanner_print_input(char *input) {
    printf("> %s\n", input); 
}

int scanner_scan_from_string(char *input, error *err) {
    lexer_token *lexer_token_arr = lexer_process_string(input, err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, err);
    if (RET_ERR == util_check_error(*err) ) {
        return RET_ERR;
    }

    parser_print_cst_node_arr(cst_node_arr);

    return RET_SUCCESS;
}



 int scanner_scan_from_file(FILE *file, char *filepath, error *err) {

    if (NULL == file) {
        size_t err_len = strlen(filepath) + 15;
        char err_msg[err_len];
        (void)snprintf(err_msg, err_len, "file not open: %s", filepath);
        *err = util_create_error(ERR_FS, ERR_CRIT_ERROR, err_msg, "the file should have been opened in beforehand.");
        if (RET_ERR == util_check_error(*err) ) {
            return RET_ERR;
        }
    }  

    char buffer[MAX_READ_BUFFER];

    int i = 0;
    while(i < MAX_LINES) {
        printf("> ");    
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            util_trim_string(buffer);
            printf("< %s\n", buffer);
            lexer_token *lexer_token_arr = lexer_process_string(buffer, err);
            if (RET_ERR == util_check_error(*err) ) {
                break;
            }
            parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, err);
            if (RET_ERR == util_check_error(*err) ) {
                break;
            }
            parser_print_cst_node_arr(cst_node_arr);
        }
        i++;
    }

    return RET_SUCCESS;
 }



int scanner_scan_from_filepath(char *filepath, error *err) {
    int result = 0;   

    // TODO strip the string!!!
    if (strlen(filepath) == 0) {
        *err = util_create_error(ERR_ARG, ERR_CRIT_ERROR, "filepath cannot be empty", "empty parameter passed to function");
        if (RET_ERR == util_check_error(*err) ) {
            return RET_ERR;
        }
    }

    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (NULL == file) {
        size_t err_len = strlen(filepath) + 14;
        char err_msg[err_len];
        (void)snprintf(err_msg, err_len, "opening file: %s", filepath);
        *err = util_create_error(ERR_FS, ERR_CRIT_ERROR, err_msg, "the file should have been opened in beforehand.");
        if (RET_ERR == util_check_error(*err) ) {
            return RET_ERR;
        }
    }
    
    result = scanner_scan_from_file(file, filepath, err);
    if (RET_ERR == util_check_error(*err) ) {
        return RET_ERR;
    }

    // Close the file if it was opened
    if (NULL != file && stdin != file) {
        fclose(file);
    }

    return result;
}


int scanner_scan_from_stdin(error *err) {
    int result = 0;   
    char *filepath = "stdin";

    FILE *file = stdin;    
    result = scanner_scan_from_file(file, filepath, err);
    if (RET_ERR == util_check_error(*err) ) {
        return RET_ERR;
    }

    return result;

}