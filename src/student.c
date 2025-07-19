#include "student.h"
#include <stdio.h>

void student_str(char* buffer, size_t size, Student* pStudent){
    snprintf(
        buffer, 
        size,
        "Student ID: %d, Name: %s, Age: %d, Sex: %c,"
        "Address: %s, Phone No.: %s",
        pStudent->id, pStudent->name, pStudent->age, pStudent->sex,
        pStudent->address, pStudent->phone_number
    );
}
