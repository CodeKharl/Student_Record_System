#include "student.h"
#include "file_util.h"

#include <stdio.h>
#include <stdlib.h>

const char* STUDENT_LABELED_FORMAT = "Student Info\n"
    "ID: %ld\n"
    "Name: %s\n"
    "Age: %d\n"
    "Sex: %c\n"
    "Address: %s\n"
    "Contact No.: %s";

const char* STUDENT_DEFAULT_FORMAT = "%ld - %s - %d - %c - %s - %s";

Student* new_student(){
    return calloc(1, sizeof(Student));
}

void delete_student(Student* p){
    if(!p) return;

    if(p->name) free(p->name);
    if(p->address) free(p->address);
    if(p->contact_number) free(p->contact_number);

    free(p);
}

static int student_snprintf(char* buffer, size_t size, const char* format, Student* pStudent){
    return snprintf(
        buffer, 
        size,
        format,
        pStudent->id, 
        pStudent->name ? pStudent->name : "(none)", 
        pStudent->age, 
        pStudent->sex,
        pStudent->address ? pStudent->address : "(none)", 
        pStudent->contact_number ? pStudent->contact_number : "(none)"
    );
}

bool set_student_str(char* buffer, Student* pStudent, const char* format){
    if(!pStudent) return false;

    size_t needed = student_snprintf(NULL, 0, format, pStudent) + 1;  
    student_snprintf(buffer, needed, format, pStudent);
    
    return true;
}
