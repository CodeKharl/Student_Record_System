#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

typedef enum{
    MALE = 'M',
    FEMALE = 'F'
} Sex;

typedef struct{
    unsigned int id;
    unsigned int age;
    Sex sex;
    char* name;
    char* address;
    char* phone_number;
} Student;

void student_str(char* buffer, size_t size, Student* pStudent);

#endif
