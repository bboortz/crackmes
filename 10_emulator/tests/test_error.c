#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "cerror.h"
#include "cstring.h"
#include "cheap.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


int func_error_external_change(error *err) {
    *err = error_create(ERR_FS, ERR_CRIT_SEVERE, "cannot open file", "file not found");
    
    return RET_SUCCESS;
}


int func_error_external_change2(error *err) {
    err->code = ERR_FS;
    err->crit = ERR_CRIT_SEVERE;
    err->message = "cannot open file";
    err->cause = "file not found";

    return RET_SUCCESS;
}


void test_error_create_default_simple_pos(void) {
    printf("\n*** test_error_create_default_simple_pos ***\n");

    error err = error_create_default();
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);
    
    error_destroy(&err);
}

void test_error_create_simple_pos(void) {
    printf("\n*** test_error_create_simple_pos ***\n");

    error err = error_create(ERR_SUCCESS, ERR_CRIT_INFO, "unknown character", "sample error");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("unknown character", err.message);
    TEST_ASSERT_EQUAL_STRING("sample error", err.cause);
    
    error_destroy(&err);
}


void test_error_create_empty_pos(void) {
    printf("\n*** test_error_create_default_empty_pos ***\n");

    error err = error_create(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    error_destroy(&err);
}

void test_error_create_message_simple_pos(void) {
    printf("\n*** test_error_create_message_simple_pos ***\n");

    error err = error_create_default();
    //char *str = "";
    char *str1 = "unknown character";
    char *str2 = "@";
    string str;

    int ret = error_create_message((char**) &str.str, str1, str2, &err);
    TEST_ASSERT_EQUAL_STRING("unknown character: \"@\"", str.str);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);

    ret = heap_free(str.str, &err);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);
    error_destroy(&err);
}


void test_error_check_change_pos(void) {
    printf("\n*** test_error_check_change_pos ***\n");

    error err = error_create(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    int ret = 0;
    
    ret = error_check(err);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);
    error_destroy(&err);
}


void test_error_create_external_change_pos(void) {
    printf("\n*** test_error_create_external_change_pos ***\n");

    error err = error_create(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);
    error_destroy(&err);

    func_error_external_change(&err);
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);

    error_destroy(&err);
}

/*

void test_error_create_external_simple_pos(void) {
    printf("\n*** test_error_create_external_simple_pos ***\n");

    error err = error_create(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    err.code = ERR_FS;
    err.crit = ERR_CRIT_SEVERE;
    err.message = "cannot open file";
    err.cause = "file not found";
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);
}

void test_error_create_default_external_change_pos(void) {
    printf("\n*** test_error_create_default_external_change_pos ***\n");

    error err = error_create_default();
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    func_error_external_change(&err);
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);

    error_print(err);
    func_error_external_change2(&err);
    error_print(err);
    TEST_ASSERT_EQUAL_INT(ERR_IO, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_ERROR, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot read from file", err.message);
    TEST_ASSERT_EQUAL_STRING("unknown", err.cause);
}


void test_error_create_simple_neg(void) {
    printf("\n*** test_error_create_simple_neg ***\n");

    error err = error_create_default();
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    err.code = ERR_FS;
    err.crit = ERR_CRIT_SEVERE;
    err.message = "cannot open file";
    err.cause = "file not found";
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);
    //error_free(&err);
}



void test_error_create_message_complex_pos(void) {
    printf("\n*** test_error_create_message_complex_pos ***\n");

    error err;
    char *err_msg;
    char *str1 = "unknown character";
    char *str2 = "@";
    error_create_message(&err_msg, str1, str2, &err);
    err = error_create(ERR_LEXER, ERR_CRIT_WARN, err_msg, "character unknown. please verify your input.");

    TEST_ASSERT_EQUAL_STRING("unknown character: \"@\"", err.message);
    TEST_ASSERT_EQUAL_STRING("character unknown. please verify your input.", err.cause);
    error_destroy(&err);
}

void test_error_free_empty_pos(void) {
    printf("\n*** test_error_free_empty_pos ***\n");

    error err;
    
    err = error_create(ERR_LEXER, ERR_CRIT_WARN, "", "character unknown. please verify your input.");

    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("character unknown. please verify your input.", err.cause);
    error_destroy(&err);
}

*/

int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test error ****************************\n");
    RUN_TEST( test_error_create_default_simple_pos );
    RUN_TEST( test_error_create_simple_pos );
    RUN_TEST( test_error_create_empty_pos );
    RUN_TEST( test_error_check_change_pos );
    
    RUN_TEST( test_error_create_external_change_pos );
    /*
    RUN_TEST( test_error_create_external_simple_pos );
    RUN_TEST( test_error_create_default_external_change_pos );
    RUN_TEST( test_error_create_simple_neg );
    RUN_TEST( test_error_create_message_simple_pos );
    RUN_TEST( test_error_create_message_complex_pos );
    RUN_TEST( test_error_free_empty_pos );
*/

    heap_print_stat();
    error err;
    heap_check(&err);
    
    return (UnityEnd());
}