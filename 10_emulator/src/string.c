#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"
#include "cheap.h"
#include "cerror.h"







int string_free(string str, error* err) {
    return heap_free_type(str.mem, err);
}


string string_alloc(size_t count, error* err) {
    allocated_mem mem = heap_alloc_type(STRING, count, sizeof(char), err);
    string str = {0};
    str.mem = mem;
    str.str = mem.ptr;
        
    return str;
}

string string_create(char* src, error* err) {
    size_t src_len = strlen(src) + 1;
    string ret = string_alloc(src_len, err);
    strncpy(ret.str, src, src_len);
        
    return ret;
}


int string_copy_charp(char** dst, char* str, error* err) {
    size_t dst_len = strlen(str) + 1; // +1 for the null-terminator
    *dst = (char*)heap_calloc(dst_len,  sizeof(char), err);
    if (*dst == NULL) {
        return RET_ERR;
    }
    
    (void)snprintf(*dst, dst_len, "%s", str);

    return RET_SUCCESS;
}