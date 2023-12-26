#ifndef CBASE_CONV_H
#define CBASE_CONV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cerror.h"


char* cbase_conv_get_binary_from_charp(unsigned char byte, error* err);
void cbase_conv_set_bit(unsigned char *ch, uint8_t position, uint8_t bit, error* err );
uint8_t cbase_conv_get_bit(unsigned char ch, uint8_t position, error* err);


#endif