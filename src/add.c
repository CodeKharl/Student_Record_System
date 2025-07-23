#include "add.h"
#include "student.h"
#include "memory_util.h"
#include "input.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Student* get_student(FILE* pFile);
static unsigned long new_std_id(FILE* pFile);
static bool is_confirm(Student* pStudent);
static void write_student(FILE* pFile, Student* pStudent);

void student_add(FILE* pFile){
    puts("Add Student");

    Student* pStudent = get_student(pFile);

    if(pStudent && is_confirm(pStudent)){
        write_student(pFile, pStudent);
    }
    
    delete_student(pStudent);
}

static Student* get_student(FILE* pFile){
    Student* pStudent = new_student();
    if(!is_allocated(pStudent)) return NULL;
    
    pStudent->name = input_name(MAX_NAME_SIZE);
    pStudent->age = input_age();
    pStudent->sex = input_sex();
    pStudent->address = input_address(MAX_ADDRESS_SIZE);
    pStudent->contact_number = input_contact_num(MAX_CONTACT_NUM_SIZE);
    pStudent->id = new_std_id(pFile);

    return pStudent;
}

static unsigned long new_std_id(FILE* pFile){
    puts("Creating new ID...");

    Student* pLast_std = get_last_student(pFile);

    if(pLast_std){
        unsigned long id = pLast_std->id + 1;
        free(pLast_std);

        return id;
    }

    puts("First student to record.");

    return 1;
}

static bool is_confirm(Student* pStudent){
    char choice;

    char* str = student_str(pStudent);
    puts(str);
    free(str);

    while(1){
        choice = get_input_char("Continue to add this student (Y/N): ");

        switch(choice){
            case 'Y':
                return true;
            case 'N':
                return false;
            default:
                puts("Invalid choice!");
                break;
        }
    }
}

static void write_student(FILE* pFile, Student* pStudent){
    if(fwrite(pStudent, sizeof(Student), 1, pFile)){
        puts("The new student was added successfully!");
    }else puts("Failed to add the new student!");

    fflush(pFile);
}
