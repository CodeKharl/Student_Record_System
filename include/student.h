#ifndef STUDENT_H
#define STUDENT_H

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

bool set_student_str(char* buffer, Student* pStudent, const char* format);

#endif
