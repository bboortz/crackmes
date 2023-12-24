#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"

#include "cerror.h"
#include "cheap.h"
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
    
    error err;
    int result = scanner_scan_from_stdin(&err);

    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);

    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
}


int main(void) {
    UNITY_BEGIN(); 
    

    printf("\n\n****** tests ****************************\n");
    RUN_TEST( test_scanner_scan_from_stdin );

    heap_print_stat();
    // error err;
    // heap_check(&err);

    return (UnityEnd());
}