#ifndef CSTACK_H
#define CSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"


#define MAX_STACK_FRAMES 64


// stack trace struct
typedef struct {
    void *stack_frames[MAX_STACK_FRAMES];
    int num_frames;
    char **symbols;
} stack_trace;




stack_trace stack_get_stack_trace(error* err);
void stack_print_stack_trace(error* err);
char* stack_get_caller(error* err);
char* stack_get_func(error* err);
char* stack_get_func_name(char* str);

#endif