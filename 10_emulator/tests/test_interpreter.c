#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "cerror.h"
#include "cpu_6502.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}


void verify_token(lexer_token exp_token, error exp_err, lexer_token token, error err) {
    // error_print(exp_err);
    //error_print(err);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.code, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.crit, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.message, err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.cause, err.cause, "error cause not correct!");
    
    // lexer_print_token(exp_token);
    //lexer_print_token(token);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.line, token.line, "token line not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.pos, token.pos, "token pos not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.type, token.type, "token type not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_token.value, token.value, "token value not correct!");
}

void verify_cst_node(parser_cst_node exp_token, error exp_err, parser_cst_node token, error err) {
    // error_print(exp_err);
    error_print(err);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.code, err.code, "error code not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_err.crit, err.crit, "error crit not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.message, err.message, "error message not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_err.cause, err.cause, "error cause not correct!");
    
    //parser_print_cst_node(exp_token);
    parser_print_cst_node(token);
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.line, token.line, "token line not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.pos, token.pos, "token pos not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.type, token.type, "token type not correct!");
    TEST_ASSERT_EQUAL_INT_MESSAGE(exp_token.num_children, token.num_children, "token children not correct!");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_token.value, token.value, "token value not correct!");

    for (int i = 0; i < token.num_children; i++) {
        verify_cst_node(exp_token.children[i], exp_err, token.children[i], err);
    }
}


void test_interpreter_interpret_cst_node_sda_sta_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_lda_number_dec_pos ***\n");

    char input[] = "LDA #42\nSTA $1000\nLDA #45\nLDX $1000\nSTX $1001\nLDY $1001";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);
        parser_print_cst_node(cst_node_arr[i]);
        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1552, cpu.ip);
    TEST_ASSERT_EQUAL_INT(45, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(42, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(42, cpu.reg_y);
    TEST_ASSERT_EQUAL_INT(6, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_lda_number_dec_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_lda_number_dec_pos ***\n");

    char input[] = "LDA #42";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(42, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_lda_number_hex_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_lda_number_dec_pos ***\n");

    char input[] = "LDA #$f0";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(240, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_ldx_number_dec_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_ldx_number_dec_pos ***\n");

    char input[] = "LDX #42";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(42, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_ldx_number_hex_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_ldx_number_hex_pos ***\n");

    char input[] = "LDX #$f0";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(240, cpu.reg_x);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_ldy_number_dec_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_ldy_number_dec_pos ***\n");

    char input[] = "LDY #42";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(42, cpu.reg_y);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_ldy_number_hex_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_ldy_number_hex_pos ***\n");

    char input[] = "LDY #$f0";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1538, cpu.ip);
    TEST_ASSERT_EQUAL_INT(240, cpu.reg_y);
    TEST_ASSERT_EQUAL_INT(1, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


void test_interpreter_interpret_cst_node_stack_number_hex_pos(void) {
    printf("\n*** test_interpreter_interpret_cst_node_stack_number_hex_pos ***\n");

    char input[] = "LDA #$f0\nPHA";

    error err = error_create_default();
    lexer_token* lexer_token_arr = lexer_process_string(input, &err);
    parser_cst_node *cst_node_arr = parser_process(lexer_token_arr, MAX_CST_NODES, &err);
    cpu_6502 cpu = cpu_6502_create();

    int i = 0;
    while (MAX_CST_NODES > i) {
        printf("%d\n", i);
        // error exp_err = error_create(test_error_types[i], test_error_crits[i], test_error_messages[i], test_error_causes[i]);

        int result = interpreter_interpret_cst_node(cst_node_arr[i], &cpu, &err);
        TEST_ASSERT_EQUAL_INT(RET_SUCCESS, result);    
        
        if (CST_END_OF_INPUT == cst_node_arr[i].type) {
            break;
        }
        i++;
    }

    TEST_ASSERT_EQUAL_INT(1539, cpu.ip);
    TEST_ASSERT_EQUAL_INT(240, cpu.reg_a);
    TEST_ASSERT_EQUAL_INT(240, cpu.mem.data[511]);
    TEST_ASSERT_EQUAL_INT(2, i);
    TEST_ASSERT_EQUAL_INT(ERR_SUCCESS, err.code);    
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test interpreter ****************************\n");
    RUN_TEST( test_interpreter_interpret_cst_node_sda_sta_pos );
    
    RUN_TEST( test_interpreter_interpret_cst_node_lda_number_dec_pos );
    RUN_TEST( test_interpreter_interpret_cst_node_lda_number_hex_pos );
    RUN_TEST( test_interpreter_interpret_cst_node_ldx_number_dec_pos );
    RUN_TEST( test_interpreter_interpret_cst_node_ldx_number_hex_pos );
    RUN_TEST( test_interpreter_interpret_cst_node_ldy_number_dec_pos );
    RUN_TEST( test_interpreter_interpret_cst_node_ldy_number_hex_pos );

    RUN_TEST( test_interpreter_interpret_cst_node_stack_number_hex_pos );

    return (UnityEnd());
}