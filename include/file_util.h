#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdio.h>
#include <stdbool.h>

#define DATA_FILE_PATH "data/student.dat"
#define DATA_FILE_PATH_INDEX "data/student_index.dat"

bool set_ptr_file(FILE** pFile, const char* file_path, const char* access_type);

#endif // !FILE_UTIL_H
#define FILE_UTIL_H


