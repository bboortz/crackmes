#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <execinfo.h>
#include <string.h>
#include "cstack.h"
#include "cheap.h"



stack_trace stack_get_stack_trace(error* err) {
    stack_trace strace = {0};
    strace.num_frames = backtrace(strace.stack_frames, MAX_STACK_FRAMES);
    strace.symbols = backtrace_symbols(strace.stack_frames, strace.num_frames);

    heap_calloc_count(1, sizeof(strace.symbols), &strace.symbols, err);

    return strace;

}


void stack_print_stack_trace(error* err) {
    stack_trace strace = stack_get_stack_trace(err);

    printf("Stack Trace from: %s\n", strace.symbols[0]);
    for (int i = 0; i < strace.num_frames; ++i) {
        char *begin = strchr(strace.symbols[i], '(');
        if (begin != NULL) {
            char *end = strchr(begin, '+');
            if (end != NULL) {
                *end = '\0'; // Truncate string at '+'
                begin++;
                if ('\0' == begin[0]) {
                    break;
                }
                printf("  %s\n", begin); // Print function name
            }
        }
    }

    // free(strace.symbols);
}

char* stack_get_func(error* err) {
    stack_trace strace = stack_get_stack_trace(err);

    char *ret = strace.symbols[2];
    // free(strace.symbols);
    
    return ret;
}

int nn = 0;
char* stack_get_caller(error* err) {
    stack_trace strace = stack_get_stack_trace(err);
    int n = 3;
    size_t str_len = strlen(strace.symbols[n]) + 1;

    char* ret;
    //printf("i: %d\n", nn);
    if (0 == nn ) {
        //printf("******* %d\n", nn);
        nn++;
        ret = (char *)heap_calloc(str_len, sizeof(char), err);
        
    } else {
        ret = (char *)heap_calloc_no_debug(str_len, sizeof(char), err);
    }
    
    if (NULL == ret) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
    }

    strncpy(ret, strace.symbols[n], str_len);

    heap_free_no_debug(strace.symbols, err);
    // free(strace.symbols); // diret free because strace.symbols has been allocated with backtrace_symbols() function
    
    return ret;
}

char* stack_get_func_name(char* str) {
    char *begin = strchr(str, '(');
        if (begin != NULL) {
            char *end = strchr(begin, '+');
            if (end != NULL) {
                *end = '\0'; // Truncate string at '+'
                begin++;
                if ('\0' == begin[0]) {
                    return begin;
                }
                return begin;
            }
        }
    
    return begin;
}
