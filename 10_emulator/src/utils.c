#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>
#include "lexer.h"


// Function to map enum values to strings
const char* util_map_error_type_to_string(error_type t) {
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
const char* util_map_error_criticality_to_string(error_criticality t) {
    static const char* type_strings[TOKEN_NUM_TYPES] = {
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

error util_create_error_default() {
    return util_create_error(ERR_SUCCESS, ERR_CRIT_INFO, "", "");    
}


// Function to create an ErrorReport
error util_create_error(error_type err_code, error_criticality err_crit, const char* err_message, const char* err_cause) {
    error err;
    err.code = err_code;
    err.crit = err_crit;
    err.message = err_message;
    err.cause = err_cause;

    if (ERR_SUCCESS != err.code ) {
        util_print_error(err);
    }

    return err;
}

int util_create_error_message(char **dst, char* str1, char* str2) {
    size_t dst_len = strlen(str1) + strlen(str1) + 5;
    *dst = (char*)malloc(dst_len * sizeof(char));

    // printf("len: %d\n", (unsigned int) dst_len);
    if (*dst == NULL) {
        return RET_ERR;
        
    }

    (void)snprintf(*dst, dst_len, "%s: \"%s\"", str1, str2);

    return RET_SUCCESS;
}

// Function to create an ErrorReport
void util_print_error(error err) {
    fprintf(stderr, "%s: %s (%d): %s - caused by: %s\n", util_map_error_criticality_to_string(err.crit), util_map_error_type_to_string(err.code), err.code, err.message, err.cause);

}


int util_check_error(error err) {
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


int util_copy_string(char** dst, char* str) {
    size_t dst_len = strlen(str) + 1; // +1 for the null-terminator

    *dst = (char*)malloc(dst_len * sizeof(char));
    if (*dst == NULL) {
        return RET_ERR;
    }
    
    (void)snprintf(*dst, dst_len, "%s", str);

    return RET_SUCCESS;
}




int util_concat_strings(char** dst, char* str1, char* str2) {
    size_t str1_len = strlen(str2);
    size_t str2_len = strlen(str1);
    size_t dst_len = str1_len + str2_len + 1; // +1 for the null-terminator

    *dst = (char*)malloc(dst_len * sizeof(char));
    if (*dst == NULL) {
        return RET_ERR;
    }

    strcpy(*dst, str1);
    strcat(*dst, str2);

    return RET_SUCCESS;
}


int util_trim_string(char *str) {
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


int util_trim_string_from_newline(char *str) {
    // Remove the newline character if it exists
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Replace newline with null terminator
    }
    return len - 1;
}

int substr(char *dst, char *src, size_t n) {
  int len = snprintf(dst, n, "%s", src);
  if (len < 0 || (unsigned) len >= sizeof dst) return -1;
  return len;
}