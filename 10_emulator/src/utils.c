#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"




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