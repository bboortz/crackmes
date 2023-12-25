#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "ccharp.h"
#include "cheap.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


void test_ccharp_copy_string_simple_pos(void) {
    printf("\n*** test_ccharp_copy_string_simple_pos ***\n");


    error err = error_create_default();
    char* src = "test string";
    char* dst;

    ccharp_copy_string(&dst, src, &err);
    TEST_ASSERT_EQUAL_STRING("test string", src);
    TEST_ASSERT_EQUAL_STRING("test string", dst);
    heap_free(dst, &err);
}

void test_ccharp_copy_string_empty_pos(void) {
    printf("\n*** test_ccharp_copy_string_simple_pos ***\n");


    error err = error_create_default();
    char* src = "";
    char* dst;

    ccharp_copy_string(&dst, src, &err);
    TEST_ASSERT_EQUAL_STRING("", src);
    TEST_ASSERT_EQUAL_STRING("", dst);
    heap_free(dst, &err);
}

void test_ccharp_copy_substring_simple_pos(void) {
    printf("\n*** test_ccharp_copy_substring_simple_pos ***\n");


    error err = error_create_default();
    char* src = "test123";
    char* dst;

    ccharp_copy_substring(&dst, src, 0, 4, &err);
    TEST_ASSERT_EQUAL_STRING("test123", src);
    TEST_ASSERT_EQUAL_STRING("test", dst);
    heap_free(dst, &err);
}


void test_ccharp_copy_substring_empty_pos(void) {
    printf("\n*** test_ccharp_copy_substring_simple_pos ***\n");


    error err = error_create_default();
    char* src = "test123";
    char* dst;

    ccharp_copy_substring(&dst, src, 0, 0, &err);
    TEST_ASSERT_EQUAL_STRING("test123", src);
    TEST_ASSERT_EQUAL_STRING("", dst);
    heap_free(dst, &err);
}

void test_ccharp_copy_substring_as_long_as_char_simple_pos(void) {
    printf("\n*** test_ccharp_copy_substring_as_long_as_char_simple_pos ***\n");


    error err = error_create_default();
    char* src = "test123";
    char* dst;

    ccharp_copy_substring_as_long_as_char(&dst, src, &err);
    TEST_ASSERT_EQUAL_STRING("test123", src);
    TEST_ASSERT_EQUAL_STRING("test", dst);
    heap_free(dst, &err);
}



int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test ccharp ****************************\n");
    
    RUN_TEST( test_ccharp_copy_string_simple_pos );
    RUN_TEST( test_ccharp_copy_string_empty_pos );
    RUN_TEST( test_ccharp_copy_substring_simple_pos );
    RUN_TEST( test_ccharp_copy_substring_empty_pos );
    RUN_TEST( test_ccharp_copy_substring_as_long_as_char_simple_pos );
    
    heap_print_stat();
    //error err;
    //heap_check(&err);

    return (UnityEnd());
}
