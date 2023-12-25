#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <execinfo.h>
#include "cerror.h"
#include "cheap.h"
#include "ccharp.h"


// Function to map enum values to strings
const char* error_map_type_to_string(error_type t) {
    static const char* type_strings[ERR_NUM_TYPES] = {
        "SUCCESS",
        "FILESYSTEM",
        "IO",
        "ARGUMENT",
        "BOUNDARY",  
        "LEXER",
        "PARSER",
        "EMULATOR",
        "INTERNAL",
    };

    if (t >= 0 && t < ERR_NUM_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}

// Function to map enum values to strings
const char* error_map_criticality_to_string(error_criticality t) {
    static const char* type_strings[ERR_CRIT_NUM_TYPES] = {
        "INFO",
        "WARNING",
        "ERROR",
        "SEVERE",
    };

    if (t >= 0 && t < ERR_CRIT_NUM_TYPES) {
        return type_strings[t];
    }

    return "Unknown"; // Return a default string for unknown enum values
}


int error_destroy(error* err) {
    /*
    if (NULL != err->message && '\0' != err->message[0]) {
        return heap_free((void*)err->message, err);
    }

    /
    if (NULL != err->cause && '\0' != err->cause[0]) {
        return heap_free((void*)err->cause, err);
    }
    */

    heap_free((void*)err->message, err);
    return heap_free((void*)err->cause, err);    
}

error error_create_default() {
    return error_create(ERR_SUCCESS, ERR_CRIT_INFO, "", "");    
}

// Function to create an ErrorReport
error error_create(error_type err_code, error_criticality err_crit, const char* err_message, const char* err_cause) {
    size_t err_message_len = strlen(err_message) + 1;
    size_t err_cause_len = strlen(err_cause) + 1;

    error err;
    err.code = err_code;
    err.crit = err_crit;

    err.message = ccharp_strndup(err_message, err_message_len, &err);
    err.cause = ccharp_strndup(err_cause, err_cause_len, &err);

    if (ERR_SUCCESS != err.code ) {
        error_print(err);
    }

    return err;
}


int error_create_message(char **dst, char* str1, char* str2, error* err) {
    size_t dst_len = strlen(str1) + strlen(str1) + 5;
    *dst = (char *)heap_calloc(dst_len, sizeof(char), err);

    // printf("len: %d\n", (unsigned int) dst_len);
    if (dst == NULL) {
        return RET_ERR;   
    }

    (void)snprintf(*dst, dst_len, "%s: \"%s\"", str1, str2);

    //allocated_mem mem = heap_alloc_type(STRING, str_len, sizeof(char), &err);

    return RET_SUCCESS;
}

/*
// int error_create_message(char **dst, char* str1, char* str2, error* err) {
int error_create_message(string *dst, char* str1, char* str2, error* err) {
    size_t dst_len = strlen(str1) + strlen(str1) + 5;
    // *dst = (char*)malloc(dst_len * sizeof(char));
    *dst = (char *)heap_calloc(dst_len, sizeof(char), err);
    *dst = string_alloc(dst_len, err);

    // printf("len: %d\n", (unsigned int) dst_len);
    if (dst == NULL) {
        return RET_ERR;
        
    }

    (void)snprintf(dst.str, dst_len, "%s: \"%s\"", str1, str2);

    //allocated_mem mem = heap_alloc_type(STRING, str_len, sizeof(char), &err);

    return RET_SUCCESS;
}
*/

// Function to create an ErrorReport
void error_print(error err) {
    fprintf(stderr, "%s: %s (%d): %s - caused by: %s\n", error_map_criticality_to_string(err.crit), error_map_type_to_string(err.code), err.code, err.message, err.cause);

}


int error_check(error err) {
    if (ERR_SUCCESS == err.code) {
        return RET_SUCCESS;
    } else if (ERR_CRIT_SEVERE == err.crit) {
        exit(EXIT_FAILURE);
    } else if (ERR_CRIT_ERROR == err.crit) {
        return RET_ERR;
    } else if (ERR_CRIT_WARN == err.crit) {
        return RET_SUCCESS;
    } 
    
    return RET_ERR;
}

