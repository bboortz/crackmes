#ifndef CHEAP_H
#define CHEAP_H


#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"


// #define HEAP_DEBUG

// heap stats struct
typedef struct {
    long calloc_count;
    long heap_count;
    long free_count;
    long alloc_size;
    void* calloc_last_addr;
    void* realloc_last_addr;
    void* free_last_addr;
} heap_stats;


// heap types
typedef enum {
    INTEGER,
    STRING,
    HEAP_NUM_TYPES
} heap_type;

typedef struct {
    heap_type type;
    void* ptr;
    size_t size;
    size_t count;
    size_t element_size;
} allocated_mem;



extern heap_stats global_heap_stats; 




// Function to map enum values to strings
const char* heap_map_type_to_string(heap_type t);
void heap_print(allocated_mem mem);
int heap_free_type(allocated_mem mem, error* err);
allocated_mem heap_alloc_type(heap_type type, size_t count, size_t size, error* err);

int heap_free_no_debug(void* ptr, error* err);
int heap_free(void* ptr, error* err);

void* heap_calloc_no_debug(size_t count, size_t size, error* err);
void *heap_calloc(size_t count, size_t size, error* err);
void heap_calloc_count(size_t count, size_t size, void* addr, error* err);
void *heap_realloc(void* oldptr, size_t size, error* err);

void  heap_print_stat();
int heap_check(error* err);

#endif