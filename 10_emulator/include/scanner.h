#ifndef SCANNER_H
#define SCANNER_H


#include <stdio.h>
#include <stdlib.h>
#include "cerror.h"


#define MAX_READ_BUFFER 1024
#define MAX_LINES 100
#define MAX_WIDTH 100


void scanner_print_input(char *input);
int scanner_scan_from_string(char *filepath, error *err);
int scanner_scan_from_file(FILE *file, char *filepath, error *err);
int scanner_scan_from_filepath(char *filepath, error *err);
int scanner_scan_from_stdin(error *err);

#endif