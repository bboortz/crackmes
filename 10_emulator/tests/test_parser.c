#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "lexer.h"
#include "parser.h"
#include "cerror.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


void verify_token(lexer_token exp_token, error exp_err, lexer_token token, error err) {
    // error_print(exp_err);
    //error_print(err);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.code, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.crit, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.message, err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.cause, err.cause, "error cause not correct!");
    
    // lexer_print_token(exp_token);
    //lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.line, token.line, "token line not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.pos, token.pos, "token pos not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.type, token.type, "token type not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_token.value, token.value, "token value not correct!");
}

void verify_cst_node(parser_cst_node exp_token, error exp_err, parser_cst_node token, error err) {
    // error_print(exp_err);
    error_print(err);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.code, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.crit, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.message, err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.cause, err.cause, "error cause not correct!");
    
    //parser_print_cst_node(exp_token);
    parser_print_cst_node(token);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.line, token.line, "token line not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.pos, token.pos, "token pos not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.type, token.type, "token type not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.num_children, token.num_children, "token children not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_token.value, token.value, "token value not correct!");

    for (int i = 0; i < token.num_children; i++) {
        verify_cst_node(exp_token.children[i], exp_err, token.children[i], err);
    }
}


void test_parser_next_token_simple_pos(void) {
    printf("\n*** test_parser_next_token_simple_pos ***\n");

    char input[] = "MOV a, 42";
    int line = 0;
    int pos = 0;

    
    error exp_err = error_create_default();
    error err = error_create_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_STRING, "MOV", &err);
    lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES, &err);
    
    parser_cst_node exp_ast_token = parser_create_cst_node_values(0, 0, CST_INSTRUCTION, "MOV", &err);
    parser_cst_node ast_token = parser_create_cst_node(&err);

    lexer_token_arr[0] = lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, lexer_token_arr[0], err);

    ast_token = parser_next_token(lexer_token_arr, 0, &err);
    verify_cst_node(exp_ast_token, exp_err, ast_token, err);

    parser_print_cst_node(ast_token);
}


void test_parser_next_token_simple_neg(void) {
    printf("\n*** test_parser_next_token_simple_neg ***\n");
    
    char input[] = ":";
    int line = 0;
    int pos = 0;

    error exp_err = error_create(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err = error_create_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_UNKNOWN, ":", &err);
    lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES, &err);
    parser_cst_node exp_ast_token = parser_create_cst_node_values(0, 0, CST_UNKNOWN, ":", &err);
    parser_cst_node ast_token = parser_create_cst_node(&err);

    lexer_token_arr[0] = lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, lexer_token_arr[0], err);

    ast_token = parser_next_token(lexer_token_arr, 0, &err);
    verify_cst_node(exp_ast_token, exp_err, ast_token, err);
}

void test_parser_next_token_simple_neg2(void) {
    printf("\n*** test_parser_next_token_simple_neg2 ***\n");

    char input[] = ":MOV a, 42";
    //int line = 0;
    //int pos = 0;

    error exp_err = error_create(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err = error_create_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_UNKNOWN, ":", &err);
    //lexer_token* lexer_token_arr = lexer_create_token_arr(MAX_TOKEN_NODES, &err);
    parser_cst_node exp_ast_token = parser_create_cst_node_values(0, 0, CST_UNKNOWN, ":", &err);
    parser_cst_node ast_token = parser_create_cst_node(&err);


    //lexer_token_arr[0] = lexer_next_token(input, &pos, &line, &err);
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    lexer_print_token_arr(lexer_token_arr);
    lexer_print_token(lexer_token_arr[0]);
    verify_token(exp_token, exp_err, lexer_token_arr[0], err);

    ast_token = parser_next_token(lexer_token_arr, 0, &err);
    verify_cst_node(exp_ast_token, exp_err, ast_token, err);
}

void test_parser_next_token_oneline_pos(void) {
    printf("\n*** test_parser_next_token_oneline_pos ***\n");

    char input[] = "MOV abc, 4200";

    int test_pos[]  = {0, 4, 7, 9, 13 };
    int test_line[] = {0, 0, 0, 0,  0};
    char *test_value[] = {"MOV", "abc", ",", "4200", ""};
    int test_token_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    int test_parser_cst_type[] = {CST_INSTRUCTION, CST_REGISTER, CST_IGNORE, CST_NUMBER,  CST_END_OF_INPUT };
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error err = error_create_default();
    parser_cst_node ast_token = parser_create_cst_node(&err);
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);

    while (MAX_CST_NODES > test) {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_token_type[test], test_value[test], &err);
        parser_cst_node exp_ast_token = parser_create_cst_node_values(test_line[test], test_pos[test], test_parser_cst_type[test], test_value[test], &err);
        
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);
        ast_token = parser_next_token(lexer_token_arr, test, &err);
        verify_cst_node(exp_ast_token, exp_err, ast_token, err);
                
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
    int test_line[] = {0, 0, 0, 0,  0,  1,  1,  1,  1, 1};
    char *test_value[] = {"MOV", "a", ",", "42", "\n", "MOV", "b", ",", "5", ""};
    int test_token_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    int test_parser_cst_type[] = {CST_INSTRUCTION, CST_REGISTER, CST_IGNORE, CST_NUMBER,  CST_IGNORE,  CST_INSTRUCTION,  CST_REGISTER,  CST_IGNORE,  CST_NUMBER, CST_END_OF_INPUT };
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error err = error_create_default();
    parser_cst_node ast_token = parser_create_cst_node(&err);
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);

    while (MAX_CST_NODES > test) {
        printf("---------------%d\n", test);
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_token_type[test], test_value[test], &err);
        parser_cst_node exp_ast_token = parser_create_cst_node_values(test_line[test], test_pos[test], test_parser_cst_type[test], test_value[test], &err);
        
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);
        ast_token = parser_next_token(lexer_token_arr, test, &err);
        verify_cst_node(exp_ast_token, exp_err, ast_token, err);
                
        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        }

        test++;
    }
}


void test_parser_process_pos(void) {
    printf("\n*** test_parser_process_pos ***\n");

    char input[] = "MOV a, 42\nMOV b, 5";

    error err = error_create_default();
    parser_cst_node* exp_ast_node_arr = parser_create_cst_node_arr(MAX_CST_NODES, &err);
    exp_ast_node_arr[0] = parser_create_cst_node_values(0, 0, CST_INSTRUCTION, "MOV", &err);
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[0], parser_create_cst_node_values(0, 4, CST_REGISTER, "a", &err), &err );
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[0], parser_create_cst_node_values(0, 7, CST_NUMBER, "42", &err), &err );
    exp_ast_node_arr[1] = parser_create_cst_node_values(1, 10, CST_INSTRUCTION, "MOV", &err);
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[1], parser_create_cst_node_values(1, 14, CST_REGISTER, "b", &err), &err );
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[1], parser_create_cst_node_values(1, 17, CST_NUMBER, "5", &err), &err );
    exp_ast_node_arr[2] = parser_create_cst_node_values(1, 18, CST_END_OF_INPUT, "", &err);
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };

    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);

    int i = 0;
    while (MAX_CST_NODES > i) {
        error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);
        verify_cst_node(exp_ast_node_arr[i], exp_err, cst_node_arr[i], err);
        
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

    error err = error_create_default();
    parser_cst_node* exp_ast_node_arr = parser_create_cst_node_arr(MAX_CST_NODES, &err);
    exp_ast_node_arr[0] = parser_create_cst_node_values(0, 0, CST_INSTRUCTION, "MOV", &err);
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[0], parser_create_cst_node_values(0, 4, CST_REGISTER, "a", &err), &err );
    exp_ast_node_arr[1] = parser_create_cst_node_values(0, 7, CST_END_OF_INPUT, "", &err);
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };

    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("lala\n");
        error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);
        verify_cst_node(exp_ast_node_arr[i], exp_err, cst_node_arr[i], err);
        
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

    error err = error_create_default();
    parser_cst_node* exp_ast_node_arr = parser_create_cst_node_arr(MAX_CST_NODES, &err);
    exp_ast_node_arr[0] = parser_create_cst_node_values(0, 0, CST_INSTRUCTION, "MOV", &err);
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[0], parser_create_cst_node_values(0, 4, CST_REGISTER, "a", &err), &err );
    parser_add_cst_node_to_cst_node(&exp_ast_node_arr[0], parser_create_cst_node_values(0, 7, CST_NUMBER, "42", &err), &err );
    exp_ast_node_arr[1] = parser_create_cst_node_values(1, 10, CST_INSTRUCTION, "MOV", &err);
    exp_ast_node_arr[2] = parser_create_cst_node_values(1, 13, CST_END_OF_INPUT, "", &err);
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };

    

    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("lala\n");
        error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);
        verify_cst_node(exp_ast_node_arr[i], exp_err, cst_node_arr[i], err);
        
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