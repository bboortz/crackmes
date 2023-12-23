#ifndef DSTRING_H
#define DSTRING_H


#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"
#include "cheap.h"



typedef struct {
    allocated_mem mem;
    char* str;
} string;



// Function to map enum values to strings

int string_free(string str, error* err);
string string_alloc(size_t count, error* err);
string string_create(char* dst, error* err);

int string_copy_charp(char** dst, char* str, error* err);

#endif