#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <execinfo.h>
#include <string.h>
#include "cbase_conv.h"
#include "cheap.h"



/*
void print_binary(unsigned char byte) {
    for (int i = 7; i >= 0; --i) {
        printf("%d", (byte >> i) & 1);
    }
    printf("\n");
}
*/


char* cbase_conv_get_binary_from_charp(unsigned char byte, error* err) {
    // Allocate memory for the binary string representation
    size_t binary_len = 8 + 1; // 8 bits + null terminator
    char* binary = (char*)heap_calloc(binary_len,  sizeof(char), err);  

    if (binary == NULL) {
        return NULL; // Memory allocation failed
    }

    binary[8] = '\0'; // Set null terminator

    for (int i = 7; i >= 0; --i) {
        binary[7 - i] = ((byte >> i) & 1) ? '1' : '0';
    }

    return binary;
}

void cbase_conv_set_bit(unsigned char *ch, uint8_t position, uint8_t bit, error* err) {
    if (position > 7) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "Invalid bit position", "Position should be between 0 and 7.");
        return;
    }

    if (bit != 0 && bit != 1) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "Invalid bit value", "Bit should be either value 0 or 1.");
        return;
    }

    unsigned char mask = 1 << position; // Create a mask for the bit position
    if (bit == 1) {
        *ch |= mask; // Set the bit at the given position to 1
    } else {
        *ch &= ~mask; // Set the bit at the given position to 0
    }
}


uint8_t cbase_conv_get_bit(unsigned char ch, uint8_t position, error* err) {
    if (position > 7) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "Invalid bit position", "Position should be between 0 and 7.");
        return RET_ERR;
    }

    unsigned char mask = 1 << position; // Create a mask for the bit position
    int bit_value = (ch & mask) ? 1 : 0;
    return bit_value;
}