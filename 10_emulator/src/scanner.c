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

int scanner_scan_from_string(char *input) {
    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);

    parser_print_cst_node_arr(cst_node_arr);

    return RET_SUCCESS;
}



 int scanner_scan_from_file(FILE *file, char *filepath) {

    if (NULL == file) {
        fprintf(stderr, "Error: file not opened: %s\n", filepath);
        return RET_ERR;
    }  

    char buffer[MAX_READ_BUFFER];

    int i = 0;
    while(i < MAX_LINES) {
        printf("> ");    
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("<%s>", buffer);
            util_trim_string(buffer);
            printf("<%s>", buffer);
            lexer_token *lexer_token_arr = lexer_process_string(buffer);
            parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);
            parser_print_cst_node_arr(cst_node_arr);
        }
        i++;
    }


    /*
    printf("> ");
    // Read from the file or stdin safely
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); // Print the content read
        lexer_token *lexer_token_arr = lexer_process_string(buffer);
        parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);
        parser_print_cst_node_arr(cst_node_arr);
        printf("> ");
    }
*/

    return RET_SUCCESS;
 }



int scanner_scan_from_filepath(char *filepath) {
    int result = 0;   

    // TODO strip the string!!!
    if (strlen(filepath) == 0) {
        printf("ERROR: filepath cannot be empty!\n");
        return RET_ERR;
    }


    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (NULL == file) {
        fprintf(stderr, "ERROR: opening file: %s\n", filepath);
        return RET_ERR;
    }
    
    result = scanner_scan_from_file(file, filepath);

    // Close the file if it was opened
    if (NULL != file && stdin != file) {
        fclose(file);
    }

    return result;
}


int scanner_scan_from_stdin(void) {
    int result = 0;   
    char *filepath = "stdin";

    FILE *file = stdin;    
    result = scanner_scan_from_file(file, filepath);

    return result;

}