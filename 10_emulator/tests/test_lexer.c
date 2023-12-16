#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "lexer.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}



void test_lexer_next_token_simple_pos(void) {
    printf("\n*** test_lex_next_token_simple_pos ***\n");
    char input[] = "MOV a, 42";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    
    token = lexer_next_token(input, &pos, &line);
    lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT(0, token.line);
    TEST_ASSERT_EQUAL_INT(0, token.pos);
    TEST_ASSERT_EQUAL_INT(TOKEN_STRING, token.type);
    TEST_ASSERT_EQUAL_STRING("MOV", token.value);
}

void test_lexer_next_token_simple_pos2(void) {
    printf("\n*** test_lexer_next_token_simple_pos2 ***\n");
    char input[] = "MOV a,";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    
    token = lexer_next_token(input, &pos, &line);
    lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT(0, token.line);
    TEST_ASSERT_EQUAL_INT(0, token.pos);
    TEST_ASSERT_EQUAL_INT(TOKEN_STRING, token.type);
    TEST_ASSERT_EQUAL_STRING("MOV", token.value);
}

void test_lexer_next_token_simple_neg(void) {
    printf("\n*** test_lex_next_token_simple_neg ***\n");
    char input[] = ":MOV a, 42";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    
    token = lexer_next_token(input, &pos, &line);
    lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT(0, token.line);
    TEST_ASSERT_EQUAL_INT(0, token.pos);
    TEST_ASSERT_EQUAL_INT(TOKEN_UNKNOWN, token.type);
    TEST_ASSERT_EQUAL_STRING(":", token.value);
}

void test_lexer_next_token_oneline_pos(void) {
    printf("\n*** test_lex_next_token_oneline_pos ***\n");
    char input[] = "MOV abc, 4200";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    int test_pos[] = {0, 4, 7, 9, 13 };
    int test_line[] = {0, 0, 0, 0, 0 };
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "abc", ",", "4200", ""};
    int test = 0;
    while (TOKEN_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        lexer_print_token(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
}

void test_lexer_next_token_oneline_pos2(void) {
    printf("\n*** test_lexer_next_token_oneline_pos2 ***\n");
    char input[] = "MOV abc,";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    int test_pos[] = {0, 4, 7, 8 };
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "abc", ",", ""};
    int test = 0;
    while (TOKEN_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        lexer_print_token(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
}


void test_lexer_next_token_oneline_neg(void) {
    printf("\n*** test_lexer_next_token_oneline_neg ***\n");
    char input[] = "MOV ?";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    int test_pos[] = {0, 4, 5 };
    int test_line[] = {0, 0, 0};
    int test_type[] = {TOKEN_STRING, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "?", ""};
    int test = 0;
    while (TOKEN_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        lexer_print_token(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
}

void test_lexer_next_token_oneline_neg2(void) {
    printf("\n*** test_lexer_next_token_oneline_neg2 ***\n");
    char input[] = " @ ?, _ - \\";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    int test_pos[] = {1, 3, 4, 6, 8, 10, 11 };
    int test_line[] = {0, 0, 0, 0, 0, 0, 0};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_COMMA, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"@", "?", ",", "_", "-", "\\", ""};
    int test = 0;
    while (TOKEN_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        lexer_print_token(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
}

void test_lexer_next_token_multiline_pos(void) {
    printf("\n*** test_lex_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";

    int line = 0;
    int pos = 0;
    lexer_token token = {0};
    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    int test = 0;
    while (TOKEN_END_OF_INPUT != token.type) {
        token = lexer_next_token(input, &pos, &line);
        lexer_print_token(token);
        TEST_ASSERT_EQUAL_INT(test_line[test], token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], token.pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], token.value);
        test++;
    }
}

void test_lexer_process_string(void) {
    printf("\n*** test_lexer_process_string ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    int test = 0;

    lexer_token *cst_token_arr = lexer_process_string(input);

    while (MAX_TOKEN_NODES > test) {
        lexer_print_token(cst_token_arr[test]);
        TEST_ASSERT_EQUAL_INT(test_line[test], cst_token_arr[test].line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], cst_token_arr[test].pos);
        TEST_ASSERT_EQUAL_INT(test_type[test], cst_token_arr[test].type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], cst_token_arr[test].value);
        
        if (TOKEN_END_OF_INPUT == cst_token_arr[test].type) {
            break;
        }

        test++;
    }
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test lexer ****************************\n");
    RUN_TEST( test_lexer_next_token_simple_pos );
    RUN_TEST( test_lexer_next_token_simple_pos2 );
    RUN_TEST( test_lexer_next_token_simple_neg );
    RUN_TEST( test_lexer_next_token_oneline_pos );
    RUN_TEST( test_lexer_next_token_oneline_pos2 );
    RUN_TEST( test_lexer_next_token_oneline_neg );
    RUN_TEST( test_lexer_next_token_oneline_neg2 );
    RUN_TEST( test_lexer_next_token_multiline_pos );
    RUN_TEST( test_lexer_process_string );

    

    return (UnityEnd());
}