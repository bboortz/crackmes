#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "cstack.h"
#include "cerror.h"
#include "cheap.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}

#include <errno.h>
#include <execinfo.h>
void test_stack_get_stack_trace(void) {

    int max = 2;
    void *stack_frames[max+2];
    int num_frames = backtrace(stack_frames, max);

    //free(*stack_frames);

    TEST_ASSERT_EQUAL_INT(max, num_frames);
    //strace.symbols = backtrace_symbols(strace.stack_frames, strace.num_frames);

    //heap_calloc_count(1, sizeof(strace.symbols), &strace.symbols, err);

}

void test_stack_get_stack_trace_simple_pos(void) {
    printf("\n*** test_stack_get_stack_trace_simple_pos ***\n");

    error err = error_create_default();
    stack_trace strace = stack_get_stack_trace(&err);
    heap_free_no_debug(strace.symbols, &err);

    TEST_ASSERT_EQUAL_INT(1, 1);
}

void test_stack_print_stack_trace_simple_pos(void) {
    printf("\n*** test_stack_print_stack_trace_simple_pos ***\n");

    error err = error_create_default();
    stack_print_stack_trace(&err);

    TEST_ASSERT_EQUAL_INT(1, 1);
}


void test_stack_get_caller_simple_pos(void) {
    printf("\n*** test_stack_get_caller_simple_pos ***\n");

    error err = error_create_default();
    error_print(err);
    char* caller = stack_get_caller(&err);

    char* caller_name = stack_get_func_name( caller );
    TEST_ASSERT_EQUAL_STRING("UnityDefaultTestRun", caller_name);
    heap_free_no_debug(caller, &err);

/*
    char* caller = stack_get_caller(err);
    printf("heap_free: %-70s --> calloc - calloc_count: %3ld - free_count: %3ld - size: %3ld bytes (%5ld kB) - last_addr: %p\n", caller, global_heap_stats.calloc_count, global_heap_stats.free_count, global_heap_stats.alloc_size, (global_heap_stats.alloc_size/1024), global_heap_stats.calloc_last_addr);
    heap_free_no_debug(caller, err);
    */
}


void test_stack_get_func_simple_pos(void) {
    printf("\n*** test_stack_get_func_simple_pos ***\n");

    error err = error_create_default();
    char* caller = stack_get_func_name( stack_get_func(&err) );
    TEST_ASSERT_EQUAL_STRING("test_stack_get_func_simple_pos", caller);
}



int main(void) {

    UNITY_BEGIN();

    printf("\n\n****** test stack ****************************\n");
    RUN_TEST( test_stack_get_stack_trace );
    RUN_TEST( test_stack_get_stack_trace_simple_pos );
    RUN_TEST( test_stack_print_stack_trace_simple_pos );
    RUN_TEST( test_stack_get_caller_simple_pos );
    RUN_TEST( test_stack_get_func_simple_pos );


    heap_print_stat();
    //error err;
    //heap_check(&err);

    return (UnityEnd());
}
