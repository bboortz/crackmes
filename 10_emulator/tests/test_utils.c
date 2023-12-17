#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
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


int func_error_external_change(error *err) {
    err->code = ERR_FS;
    err->crit = ERR_CRIT_SEVERE;
    err->message = "cannot open file";
    err->cause = "file not found";

    return RET_SUCCESS;
}

int func_error_external_change2(error *err) {
    *err = util_create_error(ERR_IO, ERR_CRIT_ERROR, "cannot read from file", "unknown");

    return RET_SUCCESS;
}

void test_util_create_error_message_real_pos(void) {
    printf("\n*** test_util_create_error_message ***\n");

    char *str = "";
    char *str1 = "unknown character";
    char *str2 = "@";
    int ret = util_create_error_message(&str, str1, str2);

    TEST_ASSERT_EQUAL_STRING("unknown character: \"@\"", str);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);
}


void test_util_create_error_message_simple_pos(void) {
    printf("\n*** test_util_create_error_message ***\n");

    char *str = "";
    char *str1 = "c";
    char *str2 = "@";
    int ret = util_create_error_message(&str, str1, str2);
    printf("str: %s\n", str);

    TEST_ASSERT_EQUAL_STRING("c: \"@\"", str);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);
}

void test_util_check_error_change_pos(void) {
    printf("\n*** test_util_check_error_change_pos ***\n");

    error err = util_create_error(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    int ret = 0;
    ret = util_check_error(err);
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, ret);
    
    func_error_external_change2(&err);
    TEST_ASSERT_EQUAL_INT(ERR_IO, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_ERROR, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot read from file", err.message);
    TEST_ASSERT_EQUAL_STRING("unknown", err.cause);

    ret = util_check_error(err);
    TEST_ASSERT_EQUAL_INT(RET_ERR, ret);
}


void test_util_create_error_external_change_pos(void) {
    printf("\n*** test_util_create_error_external_change_pos ***\n");

    error err = util_create_error(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    func_error_external_change(&err);
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);

    util_print_error(err);
    func_error_external_change2(&err);
    util_print_error(err);
    TEST_ASSERT_EQUAL_INT(ERR_IO, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_ERROR, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot read from file", err.message);
    TEST_ASSERT_EQUAL_STRING("unknown", err.cause);
}


void test_util_create_error_simple_pos(void) {
    printf("\n*** test_util_create_error_simple_pos ***\n");

    error err = util_create_error(ERR_SUCCESS, ERR_CRIT_INFO, "", "");
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

void test_util_create_error_default_external_change_pos(void) {
    printf("\n*** test_util_create_error_default_external_change_pos ***\n");

    error err = util_create_error_default();
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_INFO, err.crit);
    TEST_ASSERT_EQUAL_STRING("", err.message);
    TEST_ASSERT_EQUAL_STRING("", err.cause);

    func_error_external_change(&err);
    TEST_ASSERT_EQUAL_INT(ERR_FS, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_SEVERE, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot open file", err.message);
    TEST_ASSERT_EQUAL_STRING("file not found", err.cause);

    util_print_error(err);
    func_error_external_change2(&err);
    util_print_error(err);
    TEST_ASSERT_EQUAL_INT(ERR_IO, err.code);
    TEST_ASSERT_EQUAL_INT(ERR_CRIT_ERROR, err.crit);
    TEST_ASSERT_EQUAL_STRING("cannot read from file", err.message);
    TEST_ASSERT_EQUAL_STRING("unknown", err.cause);
}


void test_util_create_error_default_simple_pos(void) {
    printf("\n*** test_util_create_error_default_simple_pos ***\n");

    error err = util_create_error_default();
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

int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test utils ****************************\n");
    RUN_TEST( test_util_create_error_default_simple_pos );
    RUN_TEST( test_util_create_error_default_external_change_pos );
    RUN_TEST( test_util_create_error_simple_pos );
    RUN_TEST( test_util_create_error_external_change_pos );
    RUN_TEST( test_util_check_error_change_pos );
    RUN_TEST( test_util_create_error_message_simple_pos );
    RUN_TEST( test_util_create_error_message_real_pos );

    return (UnityEnd());
}