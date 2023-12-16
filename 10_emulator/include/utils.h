#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>


#define RET_SUCCESS 0
#define RET_ERR -1


int util_trim_string(char *str);
int util_trim_string_from_newline(char *str);

#endif