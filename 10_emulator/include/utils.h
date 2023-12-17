#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>


#define RET_SUCCESS 0
#define RET_ERR -1
#define RET_WARN -2


// define error type
typedef enum {
    ERR_SUCCESS,     /* all ok - success */
    ERR_FS,          /* fs issue */
    ERR_IO,          /* io issue*/
    ERR_ARG,         /* wrong argument */
    ERR_BOUNDARY,    /* boundary exceeded */
    ERR_LEXER,       /* issue during lexing */
    ERR_PARSER,      /* issue during parsing */
    ERR_EMULATOR,    /* issue during emulating */
    ERR_INTERNAL,    /* some internal issue - usually a programming mistake */
    ERR_NUM_TYPES,
} error_type;

// define error type
typedef enum {
    ERR_CRIT_INFO,
    ERR_CRIT_WARN,
    ERR_CRIT_ERROR,
    ERR_CRIT_SEVERE,
    ERR_CRIT_NUM_TYPES
} error_criticality;


// Define an error reporting struct
typedef struct {
    error_type code;
    error_criticality crit;
    const char* message;
    const char* cause;
} error;


// const char* util_map_error_type_to_string(error_type t);
// const char* util_map_error_criticality_to_string(error_criticality t);
error util_create_error_default();
error util_create_error(error_type err_code, error_criticality err_crit, const char* message, const char* cause);
int util_create_error_message(char **dst, char* str1, char* str2);
void util_print_error(error err);
int util_check_error(error err);
int util_create_string(char** dst);
int util_copy_string(char** dst, char* str);
int util_concat_strings(char** dst, char* str1, char* str2);
int util_trim_string(char *str);
int util_trim_string_from_newline(char *str);




#endif