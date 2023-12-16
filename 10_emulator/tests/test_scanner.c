#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "unity.h"
#include "scanner.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}

void test_scanner_scan_from_stdin_simple_pos(void) {
    printf("\n*** test_scanner_scan_from_stdin_simple_pos ***\n");

    int result = scanner_scan_from_stdin();
    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}

void test_scanner_scan_from_filepath_multiline_pos(void) {
    printf("\n*** test_scanner_scan_from_filepath_multiline_pos ***\n");
    char *filepath = "tests_files/multiline.s";

    int result = scanner_scan_from_filepath(filepath);
    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}

void test_scanner_scan_from_filepath_oneline_pos(void) {
    printf("\n*** test_scanner_scan_from_filepath_oneline_pos ***\n");
    char *filepath = "tests_files/oneline.s";

    int result = scanner_scan_from_filepath(filepath);
    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}

void test_scanner_scan_from_string_simple_pos(void) {
    printf("\n*** test_scanner_scan_from_string_simple_pos ***\n");
    char input[] = "MOV a, 42";

    int result = scanner_scan_from_string(input);
    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}

void test_scanner_print_input_simple_pos(void) {
    printf("\n*** test_scanner_print_input_simple_pos ***\n");
    char input[] = "MOV a, 42";

    scanner_print_input(input);
    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, 0);
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test scanner ****************************\n");
    RUN_TEST( test_scanner_print_input_simple_pos );
    RUN_TEST( test_scanner_scan_from_string_simple_pos );
    RUN_TEST( test_scanner_scan_from_filepath_oneline_pos );
    RUN_TEST( test_scanner_scan_from_filepath_multiline_pos );
    RUN_TEST( test_scanner_scan_from_stdin_simple_pos );

    return (UnityEnd());
}