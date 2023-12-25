#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerror.h"
#include "cheap.h"
#include "cstack.h"





heap_stats global_heap_stats = {0};




// Function to map enum values to strings
const char* heap_map_type_to_string(heap_type t) {
    static const char* type_strings[HEAP_NUM_TYPES] = {
        "INTEGER",
        "STRING",    
    };

    if (t >= 0 && t < HEAP_NUM_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}

// Function to print a lexer_token
void heap_print(allocated_mem mem) {
    printf("mem: {type: %s (%d), size: %ld (%ld * %ld), ptr: %p}\n", heap_map_type_to_string(mem.type), mem.type, mem.size, mem.count, mem.element_size, mem.ptr); 
}

int heap_free_type(allocated_mem mem, error* err) {

    if (mem.size <= 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "cannot free 0 or negative memory", "programming mistake");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    if (global_heap_stats.free_count == global_heap_stats.calloc_count) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "more free's than calloc's", "programming mistake.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    long next_alloc_size = global_heap_stats.alloc_size - mem.size;
    if (next_alloc_size < 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "freeing more memory than allocated.", "programming mistake.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }
  
    global_heap_stats.alloc_size -= mem.size;
    heap_free(mem.ptr, err);

    return RET_SUCCESS;
}



allocated_mem heap_alloc_type(heap_type type, size_t count, size_t size, error* err) {
    allocated_mem mem = {0};
    mem.type = type;
    mem.count = count;
    mem.element_size = size;
    mem.size = count * size;
    
    mem.ptr = heap_calloc(count, size, err);
    mem.size = size;
    global_heap_stats.alloc_size += mem.size;
    return mem;
}


int heap_free(void* ptr, error* err) {
#ifdef HEAP_DEBUG
    char* caller = stack_get_caller(err);
    printf("heap_free: %-70s --> calloc - calloc_count: %3ld - free_count: %3ld - size: %3ld bytes (%5ld kB) - calloc_last_addr: %p - free_last_addr: %p\n", caller, global_heap_stats.calloc_count, global_heap_stats.free_count, global_heap_stats.alloc_size, (global_heap_stats.alloc_size/1024), global_heap_stats.calloc_last_addr, global_heap_stats.free_last_addr);
    heap_free_no_debug(caller, err);
#endif

    int ret = heap_free_no_debug(ptr, err);

#ifdef HEAP_DEBUG
    caller = stack_get_caller(err);
    printf("heap_free: %-70s <-- calloc - calloc_count: %3ld - free_count: %3ld - size: %3ld bytes (%5ld kB) - calloc_last_addr: %p - free_last_addr: %p\n", caller, global_heap_stats.calloc_count, global_heap_stats.free_count, global_heap_stats.alloc_size, (global_heap_stats.alloc_size/1024), global_heap_stats.calloc_last_addr, global_heap_stats.free_last_addr);
    heap_free_no_debug(caller, err);
#endif
  
    return ret;
}

int heap_free_no_debug(void* ptr, error* err) {
    if (0 > global_heap_stats.heap_count) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot free memory", "more free's than allocs: 0 > global_heap_stats.heap_count");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    if (NULL == ptr) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot free memory", "Pointer is null.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    global_heap_stats.free_count++;
    global_heap_stats.heap_count--;
    global_heap_stats.free_last_addr = (void *)ptr;

    free(ptr);

    return RET_SUCCESS;
}



void* heap_calloc(size_t count, size_t size, error* err) {
#ifdef HEAP_DEBUG
    char* caller = stack_get_caller(err);
    printf("heap_allo: %-70s --> calloc - calloc_count: %3ld - free_count: %3ld - size: %3ld bytes (%5ld kB) - calloc_last_addr: %p - free_last_addr: %p\n", caller, global_heap_stats.calloc_count, global_heap_stats.free_count, global_heap_stats.alloc_size, (global_heap_stats.alloc_size/1024), global_heap_stats.calloc_last_addr, global_heap_stats.free_last_addr);
    heap_free(caller, err);
#endif

    void* ptr = heap_calloc_no_debug(count, size, err);

#ifdef HEAP_DEBUG
    caller = stack_get_caller(err);
    printf("heap_allo: %-70s <-- calloc - calloc_count: %3ld - free_count: %3ld - size: %3ld bytes (%5ld kB) - calloc_last_addr: %p - free_last_addr: %p\n", caller, global_heap_stats.calloc_count, global_heap_stats.free_count, global_heap_stats.alloc_size, (global_heap_stats.alloc_size/1024), global_heap_stats.calloc_last_addr, global_heap_stats.free_last_addr);
    heap_free(caller, err);
#endif
    return ptr;
}

void* heap_calloc_no_debug(size_t count, size_t size, error* err) {
    void* ret = NULL;

    if ((int)count <= 0 || (int)size <= 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "cannot allocate 0 or negative memory", "unclear, probably a programming mistake or unsifficient memory.");
        if (RET_ERR == error_check(*err) ) {
            return ret;
        }
    }
    ret = (char*)calloc(count, size);

    if (NULL == ret) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
        if (RET_ERR == error_check(*err) ) {
            return ret;
        }
    }

    heap_calloc_count(count, size, ret, err);
    
    return ret;
}

void heap_calloc_count(size_t count, size_t size, void* addr, error* err) {
    if ((int)count <= 0 || (int)size <= 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_ERROR, "cannot allocate 0 or negative memory", "unclear, probably a programming mistake or unsifficient memory.");
        if (RET_ERR == error_check(*err) ) {
            return;
        }
    }

    global_heap_stats.calloc_count++;
    global_heap_stats.heap_count++;
    global_heap_stats.calloc_last_addr = (void*) addr;

    global_heap_stats.alloc_size += count * size;

    // heap_print_stat();
}



void* heap_realloc(void* oldptr, size_t size, error* err) {
    //printf("%s --> realloc - count: %d - size: %d bytes (%d kB) - last_addr: %p - oldptr: %p\n", stack_get_caller(), calloc_count, calloc_size, (calloc_size/1024), calloc_last_addr, oldptr);
    
    if (NULL == oldptr) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot reallocate memory", "Pointer is null.");
        free(oldptr);
        if (RET_ERR == error_check(*err) ) {
            return NULL;
        }
    }
    void* ret = (char*)realloc(oldptr, size);

    if (NULL == ret) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
        free(oldptr);
        if (RET_ERR == error_check(*err) ) {
            return ret;
        }
    }
    oldptr = ret;

    // global_heap_stats.calloc_count;
    // global_heap_stats.calloc_size += size;
    global_heap_stats.realloc_last_addr = (void *)ret;
    
    //printf("%s <-- realloc - count: %d - size: %d bytes (%d kB) - last_addr: %p\n", stack_get_caller(), calloc_count, calloc_size, (calloc_size/1024), ret);

    return ret;
}


void heap_print_stat() {
    printf("\n*** HEAP STATS ***\n");
    printf("calloc_count:      %ld\n", global_heap_stats.calloc_count);
    printf("heap_count:        %ld\n", global_heap_stats.heap_count);
    printf("free_count:        %ld\n", global_heap_stats.free_count);
    printf("alloc_size:        %ld\n", global_heap_stats.alloc_size);
    printf("calloc_last_addr:  %p\n", global_heap_stats.calloc_last_addr);
    printf("realloc_last_addr: %p\n", global_heap_stats.realloc_last_addr);
    printf("free_last_addr:    %p\n", global_heap_stats.free_last_addr);
}

int heap_check(error* err) {
    printf("\n*** HEAP CHECK ***\n");

    if (0 < global_heap_stats.heap_count || global_heap_stats.calloc_count > global_heap_stats.free_count) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "not all memory in heap has been free'd", "programming mistake.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    if (0 > global_heap_stats.heap_count ) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "more memory free'd than allocated", "0 > global_heap_stats.heap_count");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }
    if (global_heap_stats.calloc_count < global_heap_stats.free_count) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "more memory free'd than allocated", "global_heap_stats.calloc_count < global_heap_stats.free_count");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    if (global_heap_stats.free_count > global_heap_stats.calloc_count) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "more free's than calloc's", "programming mistake.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    if (global_heap_stats.alloc_size < 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "negative size of memory allocated", "programming mistake.");
        if (RET_ERR == error_check(*err) ) {
            return RET_ERR;
        }
    }

    printf("heap check OK!\n");

    return RET_SUCCESS;
}