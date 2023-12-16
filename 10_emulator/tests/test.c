#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "lexer.h"
#include "parser.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}

/*
int test_parser_next_token_simple_pos(void) {
    printf("\n*** test_lex_next_token_simple_pos ***\n");
    char input[] = "MOV a, 42";

    int line = 0;
    int pos = 0;

    cst_node cst_token = {0};
    cst_token = lexer_next_token(input, &pos, &line);
    cst_print_node(cst_token);
    
    ast_node ast_token = {0};
    ast_node = parser_next_token(cst_token);
    ast_print_node(ast_token);

    return 1;
}

int test_lexer_next_token_simple_pos(void) {
    printf("\n*** test_lex_next_token_simple_pos ***\n");
    char input[] = "MOV a, 42";

    int line = 0;
    int pos = 0;
    cst_node token = {0};
    
    token = lexer_next_token(input, &pos, &line);
    cst_print_node(token);
    TEST_ASSERT_EQUAL_INT(0, token.line);
    TEST_ASSERT_EQUAL_INT(0, token.pos);
    TEST_ASSERT_EQUAL_INT(CST_STRING, token.type);
    TEST_ASSERT_EQUAL_STRING("MOV", token.value);
    return 1;
}

int test_lexer_next_token_simple_neg(void) {
    printf("\n*** test_lex_next_token_simple_neg ***\n");
    char input[] = ":MOV a, 42";

    int line = 0;
    int pos = 0;
    cst_node token = {0};
    
    token = lexer_next_token(input, &pos, &line);
    cst_print_node(token);
    TEST_ASSERT_EQUAL_INT(0, token.line);
    TEST_ASSERT_EQUAL_INT(0, token.pos);
    TEST_ASSERT_EQUAL_INT(CST_UNKNOWN, token.type);
    TEST_ASSERT_EQUAL_STRING("", token.value);
    return 1;
}

int test_lexer_next_token_oneline_pos(void) {
    printf("\n*** test_lex_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42";

    int line = 0;
    int pos = 0;
    cst_node token = {0};
    int test_pos[] = {0, 4, 5, 7, 9 };
    int test_line[] = {0, 0, 0, 0, 0 };
    int test_type[] = {CST_STRING, CST_STRING, CST_COMMA, CST_NUMBER, CST_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", ""};
    int test = 0;
    while (CST_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        cst_print_node(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
    
    return 1;
}

int test_lexer_next_token_multiline_pos(void) {
    printf("\n*** test_lex_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";

    int line = 0;
    int pos = 0;
    cst_node token = {0};
    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {CST_STRING, CST_STRING, CST_COMMA, CST_NUMBER,  CST_NEWLINE,  CST_STRING,  CST_STRING,  CST_COMMA,  CST_NUMBER, CST_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    int test = 0;
    while (CST_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        cst_print_node(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
    
    return 1;
}
*/


int main(void) {
    UNITY_BEGIN(); 
/*
    printf("\n\n****** test lexer ****************************\n");
    RUN_TEST( test_lexer_next_token_simple_pos );
    RUN_TEST( test_lexer_next_token_simple_neg );
    RUN_TEST( test_lexer_next_token_oneline_pos );
    RUN_TEST( test_lexer_next_token_multiline_pos );

    printf("\n\n****** test parser ****************************\n");
    RUN_TEST( test_parser_next_token_simple_pos );

*/
    

    return (UnityEnd());
}