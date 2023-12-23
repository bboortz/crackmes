#ifndef CCHARP_H
#define CCHARP_H

#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"


char *ccharp_strndup(const char *s, size_t n, error* err);

int ccharp_copy_string(char** dst, char* str, error* err);
int ccharp_copy_substring(char** dst, char* src, size_t pos, size_t n, error* err);
int ccharp_copy_substring_as_long_as_char(char** dst, char* src, error* err);
int ccharp_copy_substring_as_long_as_digit(char** dst, char* src, error* err);
int ccharp_concat_strings(char** dst, char* str1, char* str2, error* err);
void ccharp_toupper_string(char *str);
int ccharp_string_to_int(int* dst, const char *str);
long ccharp_string_to_long(int* dst, const char* str);
int ccharp_trim_string(char *str);
int ccharp_trim_string_from_newline(char *str);


#endif