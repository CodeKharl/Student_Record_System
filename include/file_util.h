#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdio.h>
#include <stdbool.h>

#define DATA_FILE_PATH "data/student.dat"
#define DATA_FILE_INDEX_PATH "data/student_index.dat"
#define DATA_TEMP_FILE_PATH "data/temp.dat"

bool set_ptr_file(FILE** pFile, const char* file_path, const char* access_type);
bool is_file_empty(FILE* pFile, const char* file_path);

#endif
#define FILE_UTIL_H


