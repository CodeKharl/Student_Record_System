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
    unsigned long id;
    unsigned int age;
    Sex sex;
    char* name;
    char* address;
    char* contact_number;
} Student;

typedef struct{
    unsigned long id;
    long offset;
} StudentIndex;

extern const char* STUDENT_LABELED_FORMAT;
extern const char* STUDENT_DEFAULT_FORMAT;

Student* new_student();
void delete_student(Student* p);

bool set_stdIndex_by_id(StudentIndex* stdIndex, const unsigned long id, FILE* pFile_index); 
bool set_last_stdIndex(StudentIndex* stdIndex, FILE* pFile_index);
bool set_std_by_index(Student* pStudent, const StudentIndex* pStd_index, FILE* pFile); 

bool set_student_str(char* buffer, Student* pStudent, const char* format);

unsigned long input_id();
char* input_name(const size_t size);
unsigned int input_age();
Sex input_sex();
char* input_address(const size_t size);
char* input_contact_num(const size_t size);

#endif
