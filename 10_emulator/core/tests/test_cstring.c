#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "cerror.h"
#include "cstring.h"
#include "cheap.h"
#include "unity.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}

void test_heap_alloc_string_simple_pos(void) {
    printf("\n*** test_heap_alloc_string_simple_pos ***\n");

    error err;
    //size_t str_len = 2;
    char* src = "test12345";
    string str = string_create(src, &err);
    //heap_print(mem);
    printf("str: %s\n", str.str);
    TEST_ASSERT_EQUAL_INT(0, (NULL == str.mem.ptr));
    TEST_ASSERT_EQUAL_INT(0, (NULL == str.str));
    TEST_ASSERT_EQUAL_STRING(src, str.str);

    str.mem.size = 2;
    int ret = string_free(str, &err);
    TEST_ASSERT_EQUAL_INT(RET_ERR, ret);

    str.mem.size = 1;
    heap_free_type(str.mem, &err);
}




/*
void test_heap_alloc_type_simple_neg(void) {
    printf("\n*** test_heap_alloc_type_simple_neg ***\n");

    error err = error_create_default();
    size_t str_len = 2;
    allocated_mem mem = heap_alloc_type(STRING, str_len, sizeof(char), &err);
    // mem.ptr = "a";
    TEST_ASSERT_EQUAL_INT(0, (NULL == mem.ptr));
    heap_print_token(mem);
    mem.size = 1;
    heap_free_type(mem, &err);
    //heap_free_type(mem, &err);
}
*/

/*
void test_heap_free_simple_neg(void) {
    printf("\n*** test_heap_free_simple_neg ***\n");

    error err = error_create_default();
    //size_t str_len = 32;
    //char* str = (char *)heap_calloc(str_len+1, sizeof(char), &err);
    char* str = (char *)malloc(0 *sizeof(char));
    str = NULL;
    TEST_ASSERT_EQUAL_INT(0, (NULL == str));
    //heap_free(str, &err);
}
*/

void test_heap_realloc_simple_pos(void) {
    printf("\n*** test_heap_realloc_simple_pos ***\n");

    TEST_ASSERT_EQUAL_INT(1, 0);
}

void test_heap_realloc_simple_neg(void) {
    printf("\n*** test_heap_realloc_simple_neg ***\n");

    TEST_ASSERT_EQUAL_INT(1, 1);
}




int main(void) {
    UNITY_BEGIN();

    printf("\n\n****** test heap ****************************\n");
    RUN_TEST( test_heap_alloc_string_simple_pos);
    //RUN_TEST( test_heap_free_simple_neg );
    // RUN_TEST( test_heap_realloc_simple_pos );
    //RUN_TEST( test_heap_realloc_simple_neg );

    heap_print_stat();
    error err;
    heap_check(&err);

    return (UnityEnd());
}
