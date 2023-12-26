#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "cerror.h"
#include "cheap.h"
#include "lexer.h"
#include "cpu.h"
#include "cpu_6502.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


void verify_token(lexer_token exp_token, error exp_err, lexer_token token, error err) {
    error_print(exp_err);
    error_print(err);
    
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


void test_cpu_current_lexer_next_token_simple_pos(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_pos ***\n");

    char input[] = "";
    int line = 0;
    int pos = 0;
    
    error exp_err = error_create_default();
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_END_OF_INPUT, "", &err);
    lexer_token token;
        
    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_simple_pos2(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_pos2 ***\n");

    char input[] = "MO";
    int line = 0;
    int pos = 0;
    
    error exp_err = error_create_default();
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_LITERAL, "MO", &err);
    lexer_token token;
        
    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_simple_pos3(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_pos3 ***\n");

    char input[] = "MOV a, 42";
    int line = 0;
    int pos = 0;

    error exp_err = error_create_default();
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_LITERAL, "MOV", &err);
    lexer_token token;

    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_simple_pos4(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_pos4 ***\n");

    char input[] = "MOV a,";
    int line = 0;
    int pos = 0;

    error exp_err = error_create_default();
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_LITERAL, "MOV", &err);
    lexer_token token;

    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_simple_pos5(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_pos5 ***\n");

    char input[] = ",";
    int line = 0;
    int pos = 0;

    error exp_err = error_create_default();
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_COMMA, ",", &err);
    lexer_token token;

    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_simple_neg(void) {
    printf("\n*** test_cpu_current_lexer_next_token_simple_neg ***\n");

    char input[] = ":MOV a, 42";
    int line = 0;
    int pos = 0;

    error exp_err = error_create(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err;
    lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_UNKNOWN, ":", &err);
    lexer_token token;

    token = cpu_current_lexer_next_token(input, &pos, &line, &err);
    verify_token(exp_token, exp_err, token, err);

    lexer_destroy_token(&exp_token, &err);
    lexer_destroy_token(&token, &err);
    error_destroy(&exp_err);
    error_destroy(&err);
}

void test_cpu_current_lexer_next_token_oneline_pos(void) {
    printf("\n*** test_lex_next_token_oneline_pos ***\n");

    char input[] = "MOV abc, 4200";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 7, 9, 13 };
    int test_line[] = {0, 0, 0, 0, 0 };
    int test_type[] = {TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "abc", ",", "4200", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", ""};
    char *test_error_causes[] = { "", "", "", "", "", ""};
    int test = 0;

    error err;
    lexer_token token;
        
    do {
        printf("********* %d\n", pos);
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);

        test++;
    } while (TOKEN_END_OF_INPUT != token.type);

    
}

void test_cpu_current_lexer_next_token_oneline_pos2(void) {
    printf("\n*** test_cpu_current_lexer_next_token_oneline_pos2 ***\n");

    char input[] = "MOV abc,";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 7, 8 };
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "abc", ",", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "" };
    char *test_error_causes[] = { "", "", "", ""};
    int test = 0;

    error err; 
    lexer_token token;

    do {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);

    
}


void test_cpu_current_lexer_next_token_oneline_pos3(void) {
    printf("\n*** test_cpu_current_lexer_next_token_oneline_pos3 ***\n");

    char input[] = "11 11";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 3, 5 };
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_NUMBER, TOKEN_NUMBER, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"11", "11", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", ""};
    char *test_error_causes[] = { "", "", ""};
    int test = 0;

    error err; 
    lexer_token token;

    do {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);

    
}


void test_cpu_current_lexer_next_token_oneline_neg(void) {
    printf("\n*** test_lexer_next_token_oneline_neg ***\n");
    
    char input[] = "MOV ?";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 4, 5 };
    int test_line[] = {0, 0, 0};
    int test_type[] = {TOKEN_LITERAL, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"MOV", "?", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_LEXER, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_WARN, ERR_CRIT_INFO};
    char *test_error_messages[] = { "", "unknown character: \"?\"", "" };
    char *test_error_causes[] = { "", "character unknown. please verify your input.", "" };
    int test = 0;

    error err;
    lexer_token token;

    do {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        if (TOKEN_END_OF_INPUT == token.type) {
            error_destroy(&exp_err);
            error_destroy(&err);
            lexer_destroy_token(&exp_token, &err);
            lexer_destroy_token(&token, &err);
            break;
        } else {
            error_destroy(&exp_err);
            error_destroy(&err);
            lexer_destroy_token(&exp_token, &err);
            lexer_destroy_token(&token, &err);
        }

        
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);
}

void test_cpu_current_lexer_next_token_oneline_neg2(void) {
    printf("\n*** test_cpu_current_lexer_next_token_oneline_neg2 ***\n");

    char input[] = "@";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 1};
    int test_line[] = {0, 0};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_END_OF_INPUT };
    char *test_value[] = {"@", ""};
    error_type test_error_types[] = {ERR_LEXER, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_WARN, ERR_CRIT_INFO};
    char *test_error_messages[] = { "unknown character: \"@\"", ""};
    char *test_error_causes[] = { "character unknown. please verify your input.", "" };
    int test = 0;

    error err;
    lexer_token token;

    do {
        printf("***** %d\n", test);

        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        if (TOKEN_END_OF_INPUT == token.type) {
            printf("#############\n");
        }
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);
}


void test_cpu_current_lexer_next_token_oneline_neg3(void) {
    printf("\n*** test_cpu_current_lexer_next_token_oneline_neg2 ***\n");

    char input[] = "@";
    int line = 0;
    int pos = 0;

    int test_pos[] = {0, 3, 4, 6, 8, 10, 11 };
    int test_line[] = {0, 0, 0, 0, 0, 0, 0};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_COMMA, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_END_OF_INPUT  };
    char *test_value[] = {"@", "?", ",", "_", "-", "\\", ""};
    error_type test_error_types[] = {ERR_LEXER, ERR_LEXER, ERR_SUCCESS, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_INFO, ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_WARN, ERR_CRIT_INFO};
    char *test_error_messages[] = { "unknown character: \"@\"", "unknown character: \"?\"", "", "unknown character: \"_\"", "unknown character: \"-\"", "unknown character: \"\\\"", "" };
    char *test_error_causes[] = { "character unknown. please verify your input.", "character unknown. please verify your input.", "", "character unknown. please verify your input.", "character unknown. please verify your input.", "character unknown. please verify your input.", "" };
    int test = 0;

    error err;
    lexer_token token;

    while (TOKEN_END_OF_INPUT != token.type) {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    }
}


void test_cpu_current_lexer_next_token_oneline_neg4(void) {
    printf("\n*** test_cpu_current_lexer_next_token_oneline_neg2 ***\n");

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

    error err;
    lexer_token token;

    while (TOKEN_END_OF_INPUT != token.type) {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    }
}

void test_cpu_current_lexer_next_token_multiline_pos(void) {
    printf("\n*** test_lex_next_token_multiline_pos ***\n");
    char input[] = "MOV a, 42\nMOV b, 5";
    int line = 0;
    int pos = 0;

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  0,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_LITERAL,  TOKEN_LITERAL,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "\n", "MOV", "b", ",", "5", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "", "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error err;
    lexer_token token;

    do {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);
}

void test_cpu_current_lexer_next_token_multiline_pos2(void) {
    printf("\n*** test_cpu_current_lexer_next_token_multiline_pos2 ***\n");
    char input[] = "\n\n";
    int line = 0;
    int pos = 0;

    int test_pos[]  = {0, 1, 2};
    int test_line[] = {0, 1, 2};
    int test_type[] = {TOKEN_NEWLINE, TOKEN_NEWLINE, TOKEN_END_OF_INPUT};
    char *test_value[] = {"\n", "\n", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS};
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO};
    char *test_error_messages[] = { "", "", "" };
    char *test_error_causes[] = { "", "", ""};
    int test = 0;

    error err;
    lexer_token token;

    do {
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        token = cpu_current_lexer_next_token(input, &pos, &line, &err);
        verify_token(exp_token, exp_err, token, err);

        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);
        lexer_destroy_token(&token, &err);
        
        test++;
    } while (TOKEN_END_OF_INPUT != token.type);
}


void test_lexer_process_string_pos(void) {
    printf("\n*** test_lexer_process_string_pos ***\n");

    char input[] = "MOV";

    int test_pos[]  = {0, 3, 5, 6};
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_LITERAL, TOKEN_END_OF_INPUT, TOKEN_COMMA, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "", ",", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "" };
    int test = 0;

    error err;
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    lexer_print_token_arr(lexer_token_arr);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_SUCCESS, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_CRIT_INFO, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.cause, "error cause not correct!");
    error_destroy(&err);

    while (MAX_TOKEN_NODES > test) {
        printf("--> %d\n", test);
        lexer_print_token(lexer_token_arr[test]);

        
        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        printf("*** alloc %d\n", test);
        err = error_create_default();
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);        
        
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);

        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        } 

        test++;
    }

    lexer_destroy_token_arr(lexer_token_arr, &err);
}


void test_lexer_process_string_pos2(void) {
    printf("\n*** test_lexer_process_string_pos2 ***\n");

    char input[] = "MOV a";

    int test_pos[]  = {0, 4, 5, 6};
    int test_line[] = {0, 0, 0, 0};
    int test_type[] = {TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_END_OF_INPUT, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", "", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "" };
    char *test_error_causes[] = { "", "", "", "" };
    int test = 0;

    error err;
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    lexer_print_token_arr(lexer_token_arr);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_SUCCESS, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_CRIT_INFO, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.cause, "error cause not correct!");
    error_destroy(&err);

    while (MAX_TOKEN_NODES > test) {
        printf("--> %d\n", test);
        lexer_print_token(lexer_token_arr[test]);

        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        printf("*** alloc %d\n", test);
        err = error_create_default();
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);        
        
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);

        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        } 

        test++;
    }

    lexer_destroy_token_arr(lexer_token_arr, &err);
}


void test_lexer_process_string_pos3(void) {
    printf("\n*** test_lexer_process_string_pos3 ***\n");

    char input[] = "MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 4, 5, 7, 9, 10, 14, 15, 17, 18 };
    int test_line[] = {0, 0, 0, 0,  0,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_NEWLINE, TOKEN_LITERAL,  TOKEN_LITERAL,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {"MOV", "a", ",", "42", "\n", "MOV", "b", ",", "5", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO,  ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "",  "", "", "", "", "", ""  };
    char *test_error_causes[] = { "", "", "", "", "", "",  "", "", "", "", "", ""  };
    int test = 0;

    error err;
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    lexer_print_token_arr(lexer_token_arr);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_SUCCESS, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_CRIT_INFO, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("", err.cause, "error cause not correct!");
    error_destroy(&err);

    while (MAX_TOKEN_NODES > test) {
        printf("--> %d\n", test);
        lexer_print_token(lexer_token_arr[test]);

        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        printf("*** alloc %d\n", test);
        err = error_create_default();
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);        
        
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);

        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        } 

        test++;
    }

    lexer_destroy_token_arr(lexer_token_arr, &err);
}


void test_lexer_process_string_neg(void) {
    printf("\n*** test_lexer_process_string_neg ***\n");

    char input[] = ":MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 1, 5, 6, 8, 10, 11, 15, 16, 18, 19 };
    int test_line[] = {0, 0, 0, 0, 0,  0,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_NUMBER, TOKEN_NEWLINE, TOKEN_LITERAL,  TOKEN_LITERAL,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {":", "MOV", "a", ",", "42", "\n", "MOV", "b", ",", "5", ""};
    error_type test_error_types[] = {ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS, ERR_SUCCESS };
    error_criticality test_error_crits[] = {ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO,  ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    char *test_error_messages[] = { "", "", "", "", "", "", "",  "", "", "", "", "", ""  };
    char *test_error_causes[] = { "", "", "", "", "", "", "",  "", "", "", "", "", ""  };
    int test = 0;

    error err;
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    lexer_print_token_arr(lexer_token_arr);
    error_print(err);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_LEXER, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ERR_CRIT_WARN, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("unknown character: \":\"", err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("character unknown. please verify your input.", err.cause, "error cause not correct!");
    error_destroy(&err);

    while (MAX_TOKEN_NODES > test) {
        printf("--> %d\n", test);
        lexer_print_token(lexer_token_arr[test]);

        error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        printf("*** alloc %d\n", test);
        err = error_create_default();
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);
        verify_token(exp_token, exp_err, lexer_token_arr[test], err);        
        
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);

        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            break;
        } 

        test++;
    }

    lexer_destroy_token_arr(lexer_token_arr, &err);
}



void test_lexer_process_string_neg2(void) {
    printf("\n*** test_lexer_process_string_neg ***\n");

    char input[] = ":MOV a, 42\nMOV b, 5";

    int test_pos[]  = {0, 1, 5, 6, 8, 10, 11, 15, 16, 18, 19 };
    int test_line[] = {0, 0, 0, 0, 0,  1,  1,  1,  1,  1, 1};
    int test_type[] = {TOKEN_UNKNOWN, TOKEN_LITERAL, TOKEN_LITERAL, TOKEN_COMMA, TOKEN_NUMBER,  TOKEN_NEWLINE,  TOKEN_LITERAL,  TOKEN_LITERAL,  TOKEN_COMMA,  TOKEN_NUMBER, TOKEN_END_OF_INPUT };
    char *test_value[] = {":", "MOV", "a", ",", "42", "", "MOV", "b", ",", "5", ""};
    // error_type test_error_types[] = {ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER, ERR_LEXER };
    // error_criticality test_error_crits[] = {ERR_CRIT_WARN, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO, ERR_CRIT_INFO };
    // char *test_error_messages[] = { "unknown character: \":\"", "", "", "", "", "", "", "", "", "", "" };
    // char *test_error_causes[] = { "character unknown. please verify your input.", "", "", "", "", "", "", "", "", "" };
    int test = 0;

    error exp_err = error_create(ERR_LEXER, ERR_CRIT_WARN, "unknown character: \":\"", "character unknown. please verify your input.");
    error err = error_create_default();
    lexer_token *lexer_token_arr = lexer_process_string(input, &err);
    //lexer_print_token_arr(lexer_token_arr);

    while (MAX_TOKEN_NODES > test) {
        // error exp_err = error_create(test_error_types[test], test_error_crits[test], test_error_messages[test], test_error_causes[test]);
        lexer_token exp_token = lexer_create_token_values(test_line[test], test_pos[test], test_type[test], test_value[test], &err);

        verify_token(exp_token, exp_err, lexer_token_arr[test], err);
        
        error_destroy(&exp_err);
        error_destroy(&err);
        lexer_destroy_token(&exp_token, &err);

        if (TOKEN_END_OF_INPUT == lexer_token_arr[test].type) {
            
            break;
        } 

        test++;
    }
}


void test_lexer_create_token_arr_simple_pos(void) {
    printf("\n*** test_lexer_create_token_arr_simple_pos ***\n");
/*
    char input[] = "";
    int line = 0;
    int pos = 0;
*/  

    //error exp_err = error_create_default();
    error err;
    // lexer_token exp_token = lexer_create_token_values(0, 0, TOKEN_END_OF_INPUT, "", &err);
    //lexer_token token;
    
    int num_elements = MAX_TOKEN_NODES;
    err = error_create_default();
    lexer_token* lexer_token_arr = lexer_create_token_arr(num_elements, &err);
    lexer_token lexer_token_arr2[10];
    

    lexer_print_token_arr(lexer_token_arr);
    printf("xxxxxxxxxxxxxxxxxxx\n");
    size_t arr_size = sizeof(*lexer_token_arr2) ;
    printf("print arr_size %ld\n", arr_size);
    
    for (int i = 0; i < num_elements; i++) {
        lexer_print_token(lexer_token_arr[i]);
        TEST_ASSERT_EQUAL_STRING("", lexer_token_arr[i].value);
        
        //lexer_destroy_token(&lexer_token_arr[i], &err);
    }
    printf("xxxxxxxxxxxxxxxxxxx\n");


    lexer_destroy_token_arr(lexer_token_arr, &err);

    // token = cpu_current_cpu_current_lexer_next_token(input, &pos, &line, &err);
    //verify_token(exp_token, exp_err, token, err);


    //lexer_destroy_token(&exp_token, &err);
    //lexer_destroy_token(&token, &err);
    //error_destroy(&exp_err);
    error_destroy(&err);
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test lexer ****************************\n");

    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos );
    
    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos );
    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos2 );
    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos3 );
    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos4 );
    RUN_TEST( test_cpu_current_lexer_next_token_simple_pos5 );
    RUN_TEST( test_cpu_current_lexer_next_token_simple_neg );
    RUN_TEST( test_cpu_current_lexer_next_token_oneline_pos );  
    RUN_TEST( test_cpu_current_lexer_next_token_oneline_pos2 );
    RUN_TEST( test_cpu_current_lexer_next_token_oneline_pos3 );
    RUN_TEST( test_cpu_current_lexer_next_token_oneline_neg );
    
    RUN_TEST( test_cpu_current_lexer_next_token_oneline_neg2 );
    RUN_TEST( test_cpu_current_lexer_next_token_multiline_pos );
    RUN_TEST( test_cpu_current_lexer_next_token_multiline_pos2 );

    RUN_TEST( test_lexer_create_token_arr_simple_pos);
    
    RUN_TEST( test_lexer_process_string_pos );
    RUN_TEST( test_lexer_process_string_pos2 );
    RUN_TEST( test_lexer_process_string_pos3 );
    
    RUN_TEST( test_lexer_process_string_neg );

    

    
    heap_print_stat();
    //error err;
    //heap_check(&err);
    

    return (UnityEnd());
}