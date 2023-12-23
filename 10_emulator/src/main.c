#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cerror.h"
#include "lexer.h"
#include "parser.h"
#include "scanner.h"


void not_ok(void) {
    printf("\nWrong password!\n");
}

void ok(void) {
    printf("\nCorrect password!\n");
    exit(0);
}



int main(int argc, char **argv) {

    printf("\n *** enjoy the crackme ***\n\n");

    printf("%d\n", argc);
    printf("%s\n", argv[0]);

    error err = error_create_default();
    int result = RET_SUCCESS;

    if (argc > 1) {
        result = scanner_scan_from_filepath(argv[1], &err);
    } else {
        result = scanner_scan_from_stdin(&err);
    }

    if (RET_ERR == result) {
        exit(EXIT_FAILURE);
    }

    //int pos = 0;
    /*
    ast_node token;
    ast_node last_token;


    strncpy(last_token.value, "NULL", sizeof(last_token.value) - 1);
    token.value[sizeof(token.value) - 1] = '\0'; 


    // Tokenizing loop
    int ip = 0;
    do {
        printf("\n*** ip = %d, last_token = <%s>\n", ip, last_token.value);
        token = get_next_token(input, &pos);

        switch (token.type) {
            case AST_INSTRUCTION:
                printf("Instruction: %s\n", token.value);
                break;
            case AST_REGISTER:
                printf("Register: %s\n", token.value);
                break;
            case AST_OPERAND:
                printf("Operand: %s\n", token.value);
                break;
            case AST_NEWLINE:
                printf("Newline\n");
                break;
            case AST_END_OF_INPUT:
                printf("End of input\n");
                break;
            case AST_UNKNOWN:
                printf("Unknown token\n");
                break;
        }

        last_token = token;
        ip++;
    } while (ip < MAX_IP && token.type != AST_END_OF_INPUT);

    */

    return 0;
}







