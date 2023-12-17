#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <utils.h>
#include "unity.h"
#include "lexer.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


void verify_token(lexer_token exp_token, error exp_err, lexer_token token, error err) {
    // util_print_error(exp_err);
    //util_print_error(err);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.code, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.crit, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.message, err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.cause, err.cause, "error cause not correct!");
    
    // lexer_print_token(exp_token);
    lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.line, token.line, "token line not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.pos, token.pos, "token pos not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.type, token.type, "token type not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_token.value, token.value, "token value not correct!");
}


void test_lexer_next_token_simple_pos(void) {
    printf("\n*** test_lexer_next_token_simple_pos ***\n");

    char input[] = "MOV a, 42";
    int line = 0;
    int pos = 0;
    
    error exp_err = util_create_error_default();
    error err = util_create_error_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_STRING, "MOV", &err);
    lexer_token token = lexer_create_token(&err);
        
    token = lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);
}

void test_lexer_next_token_simple_pos2(void) {
    printf("\n*** test_lexer_next_token_simple_pos2 ***\n");

    char input[] = "MOV a,";
    int line = 0;
    int pos = 0;

    error exp_err = util_create_error_default();
    error err = util_create_error_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_STRING, "MOV", &err);
    lexer_token token = lexer_create_token(&err);

    token = lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);
}

void test_lexer_next_token_simple_neg(void) {
    printf("\n*** test_lex_next_token_simple_neg ***\n");

    char input[] = ":MOV a, 42";
    int line = 0;
    int pos = 0;

    error exp_err = util_create_error(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err = util_create_error_default();
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_UNKNOWN, ":", &err);
    lexer_token token = lexer_create_token(&err);

    token = lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);
}

void test_lexer_next_token_oneline_pos(void) {
    printf("\n*** test_lex_next_token_oneline_pos ***\n");

    char input[] = "MOV abc, 4200";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 7, 9, 13 };
    int test_line[] = {0, 0, 0, 0, 0 };
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "abc", ",", "4200", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", ""};
    char *test_error_causes[] = { "", "", "", "", "", ""};
    int test = 0;

    error err = util_create_error_default();
    lexer_token token = lexer_create_token(&err);
        
    while (TOKEN_END_OF_INPUT != token.type) {
        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);
        
        test++;
    }
}

void test_lexer_next_token_oneline_pos2(void) {
    printf("\n*** test_lexer_next_token_oneline_pos2 ***\n");

    char input[] = "MOV abc,";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 7, 8 };
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "abc", ",", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "" };
    char *test_error_causes[] = { "", "", "", ""};
    int test = 0;

    error err = util_create_error_default();
    lexer_token token = lexer_create_token(&err);

    while (TOKEN_END_OF_INPUT != token.type) {
        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);
        
        test++;
    }
}


void test_lexer_next_token_oneline_neg(void) {
    printf("\n*** test_lexer_next_token_oneline_neg ***\n");
    
    char input[] = "MOV ?";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 5 };
    int test_line[] = {0, 0, 0};
    int test_type[] = {TOKEN_STRING, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "?", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_LEXER, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_WARN, ERR_CRIT_INFO};
    char *test_error_messages[] = { "", "unknown character: \"?\"", "" };
    char *test_error_causes[] = { "", "character unknown. please verify your input.", "" };
    int test = 0;

    error err = util_create_error_default();
    lexer_token token = lexer_create_token(&err);

    while (TOKEN_END_OF_INPUT != token.type) {
        err = util_create_error_default();

        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);
        
        test++;
    }
}

void test_lexer_next_token_oneline_neg2(void) {
    printf("\n*** test_lexer_next_token_oneline_neg2 ***\n");

    char input[] = " @ ?, _ - \\";
    int line = 0;
    int pos = 0;

    int test_pos[] = {1, 3, 4, 6, 8, 10, 11 };
    int test_line[] = {0, 0, 0, 0, 0, 0, 0};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_COMMA, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"@", "?", ",", "_", "-", "\\", ""};
    error_type test_error_types[] = {ERR_LEXER, ERR_LEXER, ERR_SUCCESS, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_INFO, ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_INFO};
    char *test_error_messages[] = { "unknown character: \"@\"", "unknown character: \"?\"", "", "unknown character: \"_\"", "unknown character: \"-\"", "unknown character: \"\\\"", "" };
    char *test_error_causes[] = { "character unknown. please verify your input.", "character unknown. please verify your input.", "", "character unknown. please verify your input.", "character unknown. please verify your input.", "character unknown. please verify your input.", "" };
    int test = 0;

    error err = util_create_error_default();
    lexer_token token = lexer_create_token(&err);

    while (TOKEN_END_OF_INPUT != token.type) {
        err = util_create_error_default();
        
        err = util_create_error_default();

        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);
        
        test++;
    }
}

void test_lexer_next_token_multiline_pos(void) {
    printf("\n*** test_lex_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";
    int line = 0;
    int pos = 0;

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error err = util_create_error_default();
    lexer_token token = lexer_create_token(&err);

    while (TOKEN_END_OF_INPUT != token.type) {
        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);
        
        test++;
    }
}

void test_lexer_process_string_pos(void) {
    printf("\n*** test_lexer_process_string_pos ***\n");

    char input[] = "MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error err = util_create_error_default();
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);

    while (MAX_TOKEN_NODES > test) {
        error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        verify_token(exp_token, exp_err, lexer_token_arr[test], err);
        
        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        }

        test++;
    }
}

void test_lexer_process_string_neg(void) {
    printf("\n*** test_lexer_process_string_neg ***\n");

    char input[] = ":MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 1, 5, 6, 8, 10, 11, 15, 16, 18, 19 };
    int test_line[] = {0, 0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_STRING, TOKEN_STRING, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_STRING,  TOKEN_STRING,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {":", "MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    // error_type test_error_types[] = {ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER };
    // error_criticality test_error_crits[] = {ERR_CRIT_WARN, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    // char *test_error_messages[] = { "unknown character: \":\"", "", "", "", "", "", "", "", "", "", "" };
    // char *test_error_causes[] = { "character unknown. please verify your input.", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error exp_err = util_create_error(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err = util_create_error_default();
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    //lexer_print_token_arr(lexer_token_arr);

    while (MAX_TOKEN_NODES > test) {
        // error exp_err = util_create_error(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        verify_token(exp_token, exp_err, lexer_token_arr[test], err);
        
        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
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
    RUN_TEST( test_lexer_process_string_pos );
    RUN_TEST( test_lexer_process_string_neg );

    

    return (UnityEnd());
}