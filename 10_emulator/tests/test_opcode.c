#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "cerror.h"
#include "opcode.h"
#include "cheap.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


extern opcode_instruction opcode_instructions[];


void test_opcode_create_instruction_simple_pos(void) {
    printf("\n*** test_opcode_create_instruction_simple_pos ***\n");

    error err;
    opcode_instruction inst = opcode_create_instruction(OPCODE_LDA, ADDRESSING_IMMEDIATE, 0xA9, 2, &err);
    opcode_print_instruction(inst);
    TEST_ASSERT_EQUAL_INT(OPCODE_LDA, inst.mnemonic);
    TEST_ASSERT_EQUAL_INT(ADDRESSING_IMMEDIATE, inst.mode);
    TEST_ASSERT_EQUAL_INT(0xA9, inst.opcode);
    TEST_ASSERT_EQUAL_INT(2, inst.length);

}

void test_opcode_get_instruction_simple_pos(void) {
    printf("\n*** test_opcode_get_instruction_simple_pos ***\n");

    error err;
    opcode_instruction exp_inst = opcode_create_instruction(OPCODE_LDA, ADDRESSING_IMMEDIATE, 0xA9, 2, &err);
    opcode_instruction inst = opcode_get_instruction(OPCODE_LDA, ADDRESSING_IMMEDIATE, &err);
    opcode_print_instruction(inst);
    TEST_ASSERT_EQUAL_INT(exp_inst.mnemonic, inst.mnemonic);
    TEST_ASSERT_EQUAL_INT(exp_inst.mode, inst.mode);
    TEST_ASSERT_EQUAL_INT(exp_inst.opcode, inst.opcode);
    TEST_ASSERT_EQUAL_INT(exp_inst.length, inst.length);



}





int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test opcode ****************************\n");
    RUN_TEST( test_opcode_create_instruction_simple_pos );
    RUN_TEST( test_opcode_get_instruction_simple_pos );

    error err;
    heap_print_stat();
    heap_check(&err);

    return (UnityEnd());
}