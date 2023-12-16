#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "utils.h"
#include "scanner.h"
#include "lexer.h"
#include "parser.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}



void test_scanner_scan_from_stdin(void) {
    printf("\n*** test_scanner_scan_from_stdin ***\n");
    
    int result = scanner_scan_from_stdin();

    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}


int main(void) {
    UNITY_BEGIN(); 

    

/*
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);

    if (RET_ERR == result) {
        exit(EXIT_FAILURE);
    }
    */

    printf("\n\n****** tests ****************************\n");
    RUN_TEST( test_scanner_scan_from_stdin );

    return (UnityEnd());
}