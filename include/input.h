#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

int get_input_int(const char* prompt);
double get_input_double(const char* prompt);
char* get_input_str(const size_t size, const char* prompt);
char get_input_char(char* prompt);

#endif
