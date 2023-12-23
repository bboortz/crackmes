#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "cerror.h"
#include "cpu_6502.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}




void test_cpu_6502_create_simple_pos(void) {
    printf("\n*** test_cpu_6502_create_simple_pos ***\n");

    //error err;
    cpu_6502 cpu = cpu_6502_create();
    TEST_ASSERT_EQUAL_INT(0xFFFC, cpu.ip);
    TEST_ASSERT_EQUAL_INT(0x0100, cpu.sp);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_y);

    cpu.reg_a = 2;
    TEST_ASSERT_EQUAL_INT(2, cpu.reg_a);

    cpu_6502_reset(&cpu);
    TEST_ASSERT_EQUAL_INT(0xFFFC, cpu.ip);
    TEST_ASSERT_EQUAL_INT(0x0100, cpu.sp);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_y);


    cpu.reg_a = 2;
    TEST_ASSERT_EQUAL_INT(2, cpu.reg_a);

    cpu_6502_destroy(&cpu);
    TEST_ASSERT_EQUAL_INT(0xFFFC, cpu.ip);
    TEST_ASSERT_EQUAL_INT(0x0100, cpu.sp);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(0, cpu.reg_y);

/*
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
    TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);
    */
}



int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test cpu 6502 ****************************\n");
    RUN_TEST( test_cpu_6502_create_simple_pos );

    return (UnityEnd());
}