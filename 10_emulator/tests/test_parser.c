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


void test_parser_next_token_simple_pos(void) {
    printf("\n*** test_parser_next_token_simple_pos ***\n");
    char input[] = "MOV a, 42";

    int line = 0;
    int pos = 0;
    lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES);

    parser_cst_node ast_token = {0};
    lexer_token_arr[0] = lexer_next_token(input, &pos, &line);
    ast_token = parser_next_token(lexer_token_arr, 0);
    parser_print_cst_node(ast_token);

    TEST_ASSERT_EQUAL_INT(0, ast_token.line);
    TEST_ASSERT_EQUAL_INT(0, ast_token.pos);
    TEST_ASSERT_EQUAL_INT(CST_INSTRUCTION, ast_token.type);
    TEST_ASSERT_EQUAL_STRING("MOV", ast_token.value);
}


void test_parser_next_token_simple_neg(void) {
    printf("\n*** test_parser_next_token_simple_neg ***\n");
    char input[] = ":";

    int line = 0;
    int pos = 0;
    lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES);

    parser_cst_node ast_token = {0};
    lexer_token_arr[0] = lexer_next_token(input, &pos, &line);
    ast_token = parser_next_token(lexer_token_arr, 0);
    parser_print_cst_node(ast_token);

    TEST_ASSERT_EQUAL_INT(0, ast_token.line);
    TEST_ASSERT_EQUAL_INT(0, ast_token.pos);
    TEST_ASSERT_EQUAL_INT(TOKEN_UNKNOWN, ast_token.type);
    TEST_ASSERT_EQUAL_STRING(":", ast_token.value);
}

void test_parser_next_token_simple_neg2(void) {
    printf("\n*** test_parser_next_token_simple_neg2 ***\n");
    char input[] = ":MOV a, 42";

    int line = 0;
    int pos = 0;
    lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES);

    parser_cst_node ast_token = {0};
    lexer_token_arr[0] = lexer_next_token(input, &pos, &line);
    ast_token = parser_next_token(lexer_token_arr, 0);
    parser_print_cst_node(ast_token);

    TEST_ASSERT_EQUAL_INT(0, ast_token.line);
    TEST_ASSERT_EQUAL_INT(0, ast_token.pos);
    TEST_ASSERT_EQUAL_INT(TOKEN_UNKNOWN, ast_token.type);
    TEST_ASSERT_EQUAL_STRING(":", ast_token.value);
}


void test_parser_next_token_oneline_pos(void) {
    printf("\n*** test_parser_next_token_oneline_pos ***\n");
    char input[] = "MOV abc, 4200";

    int test_pos[]  = {0, 4, 7, 9, 13 };
    int test_line[] = {0, 0, 0, 0,  0};
    int test_cst_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    int test_parser_cst_type[] = {CST_INSTRUCTION, CST_REGISTER, CST_IGNORE, CST_NUMBER,  CST_END_OF_INPUT };
    char *test_value[] = {"MOV", "abc", ",", "4200", ""};
    int test = 0;

    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node ast_token = parser_create_cst_node();

    while (MAX_CST_NODES > test) {
        lexer_print_token(lexer_token_arr[test]);
        ast_token = parser_next_token(lexer_token_arr, test);
        parser_print_cst_node(ast_token);
        TEST_ASSERT_EQUAL_INT(test_line[test], lexer_token_arr[test].line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], lexer_token_arr[test].pos);
        TEST_ASSERT_EQUAL_INT(test_cst_type[test], lexer_token_arr[test].type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], lexer_token_arr[test].value);
        TEST_ASSERT_EQUAL_INT(test_line[test], ast_token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], ast_token.pos);
        TEST_ASSERT_EQUAL_INT(test_parser_cst_type[test], ast_token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], ast_token.value);
        
        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        }

        test++;
    }
}

void test_parser_next_token_multiline_pos(void) {
    printf("\n*** test_parser_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_cst_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    int test_parser_cst_type[] = {CST_INSTRUCTION, CST_REGISTER, CST_IGNORE, CST_NUMBER,  CST_IGNORE,  CST_INSTRUCTION,  CST_REGISTER,  CST_IGNORE,  CST_NUMBER, CST_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    int test = 0;

    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node ast_token = parser_create_cst_node();

    while (MAX_CST_NODES > test) {
        lexer_print_token(lexer_token_arr[test]);
        ast_token = parser_next_token(lexer_token_arr, test);
        parser_print_cst_node(ast_token);
        TEST_ASSERT_EQUAL_INT(test_line[test], lexer_token_arr[test].line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], lexer_token_arr[test].pos);
        TEST_ASSERT_EQUAL_INT(test_cst_type[test], lexer_token_arr[test].type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], lexer_token_arr[test].value);
        TEST_ASSERT_EQUAL_INT(test_line[test], ast_token.line);
        TEST_ASSERT_EQUAL_INT(test_pos[test], ast_token.pos);
        TEST_ASSERT_EQUAL_INT(test_parser_cst_type[test], ast_token.type);
        TEST_ASSERT_EQUAL_STRING(test_value[test], ast_token.value);
        
        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        }

        test++;
    }
}


void test_parser_process_pos(void) {
    printf("\n*** test_parser_process_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";

    parser_cst_node* test_cst_node_arr = parser_create_cst_node_arr(MAX_CST_NODES);
    test_cst_node_arr[0].line = 0;
    test_cst_node_arr[0].pos = 0;
    test_cst_node_arr[0].type = CST_INSTRUCTION;
    test_cst_node_arr[0].num_children = 2;
    test_cst_node_arr[0].children = parser_create_cst_node_arr(2);
    test_cst_node_arr[0].children[0].line = 0;
    test_cst_node_arr[0].children[0].pos = 4;
    test_cst_node_arr[0].children[0].type = CST_REGISTER;
    test_cst_node_arr[0].children[0].num_children = 0;
    test_cst_node_arr[0].children[1].line = 0;
    test_cst_node_arr[0].children[1].pos = 7;
    test_cst_node_arr[0].children[1].type = CST_NUMBER;
    test_cst_node_arr[0].children[1].num_children = 0;
    test_cst_node_arr[1].line = 1;
    test_cst_node_arr[1].pos = 10;
    test_cst_node_arr[1].type = CST_INSTRUCTION;
    test_cst_node_arr[1].num_children = 2;
    test_cst_node_arr[1].children = parser_create_cst_node_arr(2);
    test_cst_node_arr[1].children[0].line = 1;
    test_cst_node_arr[1].children[0].pos = 14;
    test_cst_node_arr[1].children[0].type = CST_REGISTER;
    test_cst_node_arr[1].children[0].num_children = 0;
    test_cst_node_arr[1].children[1].line = 1;
    test_cst_node_arr[1].children[1].pos = 17;
    test_cst_node_arr[1].children[1].type = CST_NUMBER;
    test_cst_node_arr[1].children[1].num_children = 0;
    test_cst_node_arr[2].line = 1;
    test_cst_node_arr[2].pos = 18;
    test_cst_node_arr[2].type = CST_END_OF_INPUT;
    test_cst_node_arr[2].num_children = 0;
 
    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);

    int i = 0;
    while (MAX_CST_NODES > i) {
        //lexer_print_token(lexer_token_arr[test]);
        parser_print_cst_node(cst_node_arr[i]);
        
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].line, cst_node_arr[i].line);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].pos, cst_node_arr[i].pos);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].type, cst_node_arr[i].type);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].num_children, cst_node_arr[i].num_children);

        for (int j = 0; j < test_cst_node_arr[i].num_children; j++) {
            parser_cst_node test_child = test_cst_node_arr[i].children[j];
            parser_cst_node child = cst_node_arr[i].children[j];
            TEST_ASSERT_EQUAL_INT(test_child.line, child.line);
            TEST_ASSERT_EQUAL_INT(test_child.pos, child.pos);
            TEST_ASSERT_EQUAL_INT(test_child.type, child.type);
            TEST_ASSERT_EQUAL_INT(test_child.num_children, child.num_children);
        }
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }

        i++;
    }
    TEST_ASSERT_EQUAL_INT(2, i);
}


void test_parser_process_neg(void) {
    printf("\n*** test_parser_process_neg ***\n");
    char input[] = "MOV a, ";

    parser_cst_node* test_cst_node_arr = parser_create_cst_node_arr(MAX_CST_NODES);
    test_cst_node_arr[0].line = 0;
    test_cst_node_arr[0].pos = 0;
    test_cst_node_arr[0].type = CST_INSTRUCTION;
    test_cst_node_arr[0].num_children = 1;
    test_cst_node_arr[0].children = parser_create_cst_node_arr(2);
    test_cst_node_arr[0].children[0].line = 0;
    test_cst_node_arr[0].children[0].pos = 4;
    test_cst_node_arr[0].children[0].type = CST_REGISTER;
    test_cst_node_arr[0].children[0].num_children = 0;
    test_cst_node_arr[1].line = 0;
    test_cst_node_arr[1].pos = 7;
    test_cst_node_arr[1].type = CST_END_OF_INPUT;
    test_cst_node_arr[1].num_children = 0;
 
    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);

    int i = 0;
    while (MAX_CST_NODES > i) {
        //lexer_print_token(lexer_token_arr[test]);
        parser_print_cst_node(cst_node_arr[i]);
        
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].line, cst_node_arr[i].line);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].pos, cst_node_arr[i].pos);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].type, cst_node_arr[i].type);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].num_children, cst_node_arr[i].num_children);

        for (int j = 0; j < test_cst_node_arr[i].num_children; j++) {
            parser_cst_node test_child = test_cst_node_arr[i].children[j];
            parser_cst_node child = cst_node_arr[i].children[j];
            TEST_ASSERT_EQUAL_INT(test_child.line, child.line);
            TEST_ASSERT_EQUAL_INT(test_child.pos, child.pos);
            TEST_ASSERT_EQUAL_INT(test_child.type, child.type);
            TEST_ASSERT_EQUAL_INT(test_child.num_children, child.num_children);
        }
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }

        i++;
    }
    TEST_ASSERT_EQUAL_INT(1, i);
}

void test_parser_process_neg2(void) {
    printf("\n*** test_parser_process_neg2 ***\n");
    char input[] = "MOV a, 42\nMOV";

    parser_cst_node* test_cst_node_arr = parser_create_cst_node_arr(MAX_CST_NODES);
    test_cst_node_arr[0].line = 0;
    test_cst_node_arr[0].pos = 0;
    test_cst_node_arr[0].type = CST_INSTRUCTION;
    test_cst_node_arr[0].num_children = 2;
    test_cst_node_arr[0].children = parser_create_cst_node_arr(2);
    test_cst_node_arr[0].children[0].line = 0;
    test_cst_node_arr[0].children[0].pos = 4;
    test_cst_node_arr[0].children[0].type = CST_REGISTER;
    test_cst_node_arr[0].children[0].num_children = 0;
    test_cst_node_arr[0].children[1].line = 0;
    test_cst_node_arr[0].children[1].pos = 7;
    test_cst_node_arr[0].children[1].type = CST_NUMBER;
    test_cst_node_arr[0].children[1].num_children = 0;
    test_cst_node_arr[1].line = 1;
    test_cst_node_arr[1].pos = 10;
    test_cst_node_arr[1].type = CST_INSTRUCTION;
    test_cst_node_arr[1].num_children = 0;
    test_cst_node_arr[1].children = parser_create_cst_node_arr(2);
    test_cst_node_arr[2].line = 1;
    test_cst_node_arr[2].pos = 13;
    test_cst_node_arr[2].type = CST_END_OF_INPUT;
    test_cst_node_arr[2].num_children = 0;
 
    lexer_token *lexer_token_arr = lexer_process_string(input);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES);

    int i = 0;
    while (MAX_CST_NODES > i) {
        //lexer_print_token(lexer_token_arr[test]);
        parser_print_cst_node(cst_node_arr[i]);
        
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].line, cst_node_arr[i].line);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].pos, cst_node_arr[i].pos);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].type, cst_node_arr[i].type);
        TEST_ASSERT_EQUAL_INT(test_cst_node_arr[i].num_children, cst_node_arr[i].num_children);

        for (int j = 0; j < test_cst_node_arr[i].num_children; j++) {
            parser_cst_node test_child = test_cst_node_arr[i].children[j];
            parser_cst_node child = cst_node_arr[i].children[j];
            TEST_ASSERT_EQUAL_INT(test_child.line, child.line);
            TEST_ASSERT_EQUAL_INT(test_child.pos, child.pos);
            TEST_ASSERT_EQUAL_INT(test_child.type, child.type);
            TEST_ASSERT_EQUAL_INT(test_child.num_children, child.num_children);
        }
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }

        i++;
    }
    TEST_ASSERT_EQUAL_INT(2, i);
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test parser ****************************\n");
    RUN_TEST( test_parser_next_token_simple_pos );
    RUN_TEST( test_parser_next_token_simple_neg );
    RUN_TEST( test_parser_next_token_simple_neg2 );
    RUN_TEST( test_parser_next_token_oneline_pos );
    RUN_TEST( test_parser_next_token_multiline_pos );
    RUN_TEST( test_parser_process_pos );
    RUN_TEST( test_parser_process_neg );
    RUN_TEST( test_parser_process_neg2 );

    return (UnityEnd());
}