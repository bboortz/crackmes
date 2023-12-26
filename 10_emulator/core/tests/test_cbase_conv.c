#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unity.h"
#include "cbase_conv.h"
#include "cerror.h"
#include "cheap.h"



// Define setup and t   eardown functions if needed
void setUp() {
    // Initialize resources before each test
}

void tearDown() {
    // Free resources after each test
}



void test_cbase_conv_complex_pos(void) {
    printf("\n*** test_cbase_conv_set_bit_simple_pos ***\n");

    error err;
    unsigned char c = '\0';
    uint8_t b = 0;
    char *str;

    b = cbase_conv_get_bit(c, 0, &err);
    str = cbase_conv_get_binary_from_charp(c, &err);
    printf("%2c: %3d, %2d, %s\n", c, c, b, str);
    TEST_ASSERT_EQUAL_INT(0, c);
    TEST_ASSERT_EQUAL_INT(0, b);
    heap_free(str, &err);

    cbase_conv_set_bit(&c, 0, 1, &err);
    b = cbase_conv_get_bit(c, 0, &err);
    str = cbase_conv_get_binary_from_charp(c, &err);
    printf("%2c: %3d, %2d, %s\n", c, c, b, str);
    TEST_ASSERT_EQUAL_INT(1, c);
    TEST_ASSERT_EQUAL_INT(1, b);
    heap_free(str, &err);

    cbase_conv_set_bit(&c, 6, 1, &err);
    cbase_conv_set_bit(&c, 0, 0, &err);
    b = cbase_conv_get_bit(c, 0, &err);
    str = cbase_conv_get_binary_from_charp(c, &err);
    printf("%1c: %3d, %2d, %s\n", c, c, b, str);
    TEST_ASSERT_EQUAL_INT(64, c);
    TEST_ASSERT_EQUAL_INT(0, b);
    heap_free(str, &err);
}


int main(void) {
    UNITY_BEGIN(); 

    printf("\n\n****** test cbase_conv ****************************\n");
    RUN_TEST( test_cbase_conv_complex_pos );
   

    heap_print_stat();
    error err;
    heap_check(&err);
    
    return (UnityEnd());
}