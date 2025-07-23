#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

#define MAX_NAME_SIZE 40
#define MAX_ADDRESS_SIZE 30
#define MAX_CONTACT_NUM_SIZE 15

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
    char* contact_number;
} Student;

Student* new_student();
void delete_student(Student* p);

char* student_str(Student* pStudent);

char* input_name(const size_t size);
unsigned int input_age();
Sex input_sex();
char* input_address(const size_t size);
char* input_contact_num(const size_t size);

#endif
