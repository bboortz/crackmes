#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "ccharp.h"
#include "cerror.h"
#include "cheap.h"




/*
int ccharp_concat_strings(char** dst, char* str1, char* str2, error* err) {
    size_t str1_len = strlen(str2);
    size_t str2_len = strlen(str1);
    size_t dst_len = str1_len + str2_len + 1; // +1 for the null-terminator

    // TODO realloc??
    // *dst = (char*)ccharp_malloc(dst_len * sizeof(char), err);
    *dst = (char*) ccharp_realloc(*dst, dst_len * sizeof(char), err);
    
    //dynamic_array = resized_array;
    if (*dst == NULL) {
        return RET_ERR;
    }

    strcpy(*dst, str1);
    strcat(*dst, str2);

    return RET_SUCCESS;
}
*/

char *ccharp_strndup(const char *s, size_t n, error* err) {
    char *p;
    size_t n1;

    for (n1 = 0; n1 < n && s[n1] != '\0'; n1++)
        continue;
    p = heap_calloc(n + 1, sizeof(char), err);
    if (p != NULL) {
        memcpy(p, s, n1);
        p[n1] = '\0';
    }
    return p;
}


int ccharp_copy_string(char** dst, char* src, error* err) {
    size_t dst_len = strlen(src) + 1; // +1 for the null-terminator

    return ccharp_copy_substring(dst, src, 0, dst_len, err);
}


int ccharp_copy_substring(char** dst, char* src, size_t pos, size_t n, error* err) {
    size_t dst_len = n + 1; // +1 for the null-terminator
    while (pos > 0) {
        dst++;
        pos--;
    }
    
    *dst = (char*) heap_calloc(dst_len, sizeof(char), err);
    //error_print(*err);
    if (*dst == NULL) {
        return RET_ERR;
    }
    
    (void)snprintf(*dst, dst_len, "%s", src);

    return n;
}


int ccharp_copy_substring_as_long_as_char(char** dst, char* src, error* err) {
    
    size_t src_len = strlen(src); // +1 for the null-terminator
    size_t dst_len = 0;
    char* src_begin = src;

    if (0 == src_len) {
        return RET_SUCCESS;
    }

    if (! isalpha(*src)) {
        return RET_SUCCESS;
    }

    while (isalpha(*src)) {
        dst_len++;
        src++;
    }
    //printf("%ld\n", dst_len);

    return ccharp_copy_substring(dst, src_begin, 0, dst_len, err);
}


int ccharp_copy_substring_as_long_as_digit(char** dst, char* src, error* err) {
    
    size_t src_len = strlen(src); // +1 for the null-terminator
    size_t dst_len = 0;
    char* src_begin = src;

    if (0 == src_len) {
        return RET_SUCCESS;
    }

    if (! isdigit(*src)) {
        return RET_SUCCESS;
    }

    while (isdigit(*src)) {
        dst_len++;
        src++;
    }
    //printf("%ld\n", dst_len);

    return ccharp_copy_substring(dst, src_begin, 0, dst_len, err);
}



void ccharp_toupper_string(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}


int ccharp_trim_string(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Trim leading white spaces
    while (isspace(str[start])) {
        start++;
    }

    // Trim trailing white spaces
    while (end > start && isspace(str[end])) {
        end--;
    }

    // Shift the non-space characters to the beginning of the string
    int shiftIndex = 0;
    for (int i = start; i <= end; i++) {
        str[shiftIndex++] = str[i];
    }

    // Null-terminate the trimmed string
    str[shiftIndex] = '\0';

    return strlen(str);
}


int ccharp_trim_string_from_newline(char *str) {
    // Remove the newline character if it exists
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Replace newline with null terminator
    }
    return len - 1;
}


int ccharp_string_to_int(int* dst, const char *str) {
    return (int) ccharp_string_to_long(dst, str);
}

long ccharp_string_to_long(int* dst, const char* str) {
    char* endptr = NULL;
    errno = 0; // Reset errno before the call
    long converted = strtol(str, &endptr, 10); // Convert string to long

    // Check for conversion errors
    if ((errno == ERANGE && (converted == LONG_MAX || converted == LONG_MIN)) ||
        (errno != 0 && converted == 0)) {
        return RET_ERR; // Conversion error: out of range or invalid
    }

    // Check for non-numeric characters in the string
    if (endptr == str || *endptr != '\0') {
        return RET_ERR; // Non-numeric characters present
    }

    *dst = converted; // Store the result in the output parameter
    return RET_SUCCESS;
}

int ccharp_substr(char *dst, char *src, size_t n) {
  int len = snprintf(dst, n, "%s", src);
  if (len < 0 || (unsigned) len >= sizeof dst) return -1;
  return len;
}


/*
void print_tack(char *file, int line) {
    unsigned long long* rsp; // Pointer to the stack (for x86_64)

    // Get the current stack pointer (for x86_64)
    __asm__("mov %%rsp, %0" : "=r" (rsp));

    printf("\n------------------------\nPrinting stack (%s, %d):\n", file, line);

    // Traverse and print the stack contents
    for (int i = 0; i < 10; ++i) {
        long long unsigned int* addr = rsp + i;
        printf("Stack address [%p]: Value [%lld]\n", (void *)addr, *(rsp + i));
    }
    printf("\n------------------------\n");

}
*/


    /*

static int malloc_count = 0;
static int malloc_size = 0;
static void *malloc_last_addr = 0;
void *ccharp_malloc(size_t size, error* err) {
    void* ret = NULL;
    if (size <= 0) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot allocate 0 or negative memory", "unclear, probably a programming mistake or unsifficient memory.");
        if (RET_ERR == error_check(*err) ) {
            return ret;
        }
    }

    ret = (char*)malloc(size);

    if (NULL == ret) {
        *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
        if (RET_ERR == error_check(*err) ) {
            return ret;
        }
    }

    malloc_count++;
    malloc_size += size;
    malloc_last_addr = (void *)ret;
    printf("%s --> malloc - count: %d - size: %d bytes (%d kB) - last_addr: %p\n", ccharp_get_caller(), malloc_count, malloc_size, (malloc_size/1024), ret);

    return ret;
}



*/