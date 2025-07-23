#include "student.h"
#include "input.h"
#include "memory_util.h"

#include <stdio.h>
#include <stdlib.h>

const static char* student_str_format = "%d - %s - %d - %c - %s - %s";

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

static int student_snprintf(char* buffer, size_t size, Student* pStudent){
     return snprintf(
            buffer, 
            size,
            student_str_format,
            pStudent->id, 
            pStudent->name ? pStudent->name : "(none)", 
            pStudent->age, 
            pStudent->sex,
            pStudent->address ? pStudent->address : "(none)", 
            pStudent->contact_number ? pStudent->contact_number : "(none)"
     );
}

char* student_str(Student* pStudent){
    size_t needed = student_snprintf(NULL, 0, pStudent) + 1;  
    char* buffer = malloc(needed);

    if(is_allocated(buffer)){
        student_snprintf(buffer, needed, pStudent);
        
        return buffer;
    }

    return NULL;
}

char* input_name(const size_t size){
    return get_input_str(size, "Enter student name: ");
}

unsigned int input_age(){
    return get_input_int("Enter student age: ");
}

Sex input_sex(){
    char input;

    while(1){
        input = get_input_char("Enter student sex (M/F) : ");

        switch(input){
            case MALE:
            case FEMALE:
                return input;
            default:
                puts("Invalid input! Please try again");
                break;
        }
    }
}

char* input_address(const size_t size){
    return get_input_str(size, "Enter student address: ");
}

char* input_contact_num(const size_t size){
    return get_input_str(size, "Enter student contact number: ");
}
