#include "add.h"
#include "student.h"
#include "memory_util.h"
#include "input.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static Student* get_student(unsigned int new_id);
static int new_std_id(FILE* pFile);
static bool set_last_std(FILE* pFile, Student* pStd);
static bool is_confirm(Student* pStudent);
static void write_student(FILE* pFile, Student* pStudent);

void student_add(FILE* pFile){
    if(pFile == NULL){
        puts("Data file failed to open!");
        return;
    }

    puts("Add Student");

    int new_id = new_std_id(pFile);
    Student* pStudent = get_student(new_id);

    if(pStudent && is_confirm(pStudent)){
        write_student(pFile, pStudent);
    }
    
    delete_student(pStudent);
}

static Student* get_student(unsigned int new_id){
    Student* pStudent = new_student();
    if(!is_allocated(pStudent)) return NULL;
    
    pStudent->id = new_id;
    pStudent->name = input_name(MAX_NAME_SIZE);
    pStudent->age = input_age();
    pStudent->sex = input_sex();
    pStudent->address = input_address(MAX_ADDRESS_SIZE);
    pStudent->contact_number = input_contact_num(MAX_CONTACT_NUM_SIZE);

    return pStudent;
}

static int new_std_id(FILE* pFile){
    Student pLast_std;

    return set_last_std(pFile, &pLast_std) ? pLast_std.id + 1 : 1;
}

static bool set_last_std(FILE* pFile, Student* pStd){
    fseek(pFile, 0, SEEK_END);
    if(ftell(pFile) == 0){
        return false;
    }

    fseek(pFile, -sizeof(Student), SEEK_END);

    return fread(pStd, sizeof(Student), 1, pFile) == 1;
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
