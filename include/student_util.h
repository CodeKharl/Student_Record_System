#ifndef STUDENT_UTIL_H
#define STUDENT_UTIL_H

#include "student.h"

#include <stdio.h>

void print_student(Student* pStudent, const char* format);

bool set_stdIndex_by_id(StudentIndex* stdIndex, const unsigned long id, FILE* pFile_index); 
bool set_last_stdIndex(StudentIndex* stdIndex, FILE* pFile_index);
bool set_std_by_index(Student* pStudent, const StudentIndex* pStd_index, FILE* pFile); 

unsigned long input_id();
char* input_name(const size_t size);
unsigned int input_age();
Sex input_sex();
char* input_address(const size_t size);
char* input_contact_num(const size_t size);

#endif
