#include "add.h"
#include "student.h"
#include "memory_util.h"
#include "input.h"
#include "student_util.h"
#include "sys_util.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static void set_input_student(Student* pStudent, FILE* pStd_file, FILE* pStd_index_file);
static unsigned long new_std_id(FILE* pStd_file, FILE* pStd_index_file);
static bool is_confirm(Student* pStudent);
static void write_student(FILE* pStd_file, FILE* pStd_index_file, Student* pStudent);
static bool write_student_index(StudentIndex* pStd_index, FILE* pStd_index_file);
static bool fwrite_chars(char* pStr, FILE* pStd_file);

void student_add(FILE** pStd_file, FILE** pStd_index_file){
    puts("\nAdd Student");

    Student* pStudent = new_student();
    if(!is_allocated(pStudent)) return;

    set_input_student(pStudent, *pStd_file, *pStd_index_file);

    if(is_confirm(pStudent)){
        write_student(*pStd_file, *pStd_index_file, pStudent);
    }
    
    delete_student(pStudent);
}

static void set_input_student(Student* pStudent, FILE* pStd_file, FILE* pStd_index_file){
    pStudent->name = input_name(MAX_NAME_SIZE);
    pStudent->age = input_age();
    pStudent->sex = input_sex();
    pStudent->address = input_address(MAX_ADDRESS_SIZE);
    pStudent->contact_number = input_contact_num(MAX_CONTACT_NUM_SIZE);
    pStudent->id = new_std_id(pStd_file, pStd_index_file);
}

static unsigned long new_std_id(FILE* pStd_file, FILE* pStd_index_file){
    StudentIndex last_stdIndex;

    puts("\nCreating new ID...");

    if(set_last_stdIndex(&last_stdIndex, pStd_index_file)){
        return last_stdIndex.id + 1;
    }

    puts("First student to record.");
    
    return 1;
}

static bool is_confirm(Student* pStudent){
    char choice;

    printf("\n");
    print_student(pStudent, STUDENT_LABELED_FORMAT);

    while(1){
        choice = get_input_char("\nContinue to add this student (Y/N): ");

        switch(toupper(choice)){
            case YES:
                return true;
            case NO:
                return false;
            default:
                puts("Invalid choice!");
                break;
        }
    }
}

static void write_student(FILE* pStd_file, FILE* pStd_index_file, Student* pStudent){
    StudentIndex stdIndex;

    stdIndex.id = pStudent->id;
    stdIndex.offset = ftell(pStd_file);

    if(!write_student_index(&stdIndex, pStd_index_file)){
        return;
    }

    fwrite(&pStudent->id, sizeof(pStudent->id), 1, pStd_file);
    fwrite(&pStudent->age, sizeof(pStudent->age), 1, pStd_file);
    fwrite(&pStudent->sex, sizeof(pStudent->sex), 1, pStd_file);
    
    if(fwrite_chars(pStudent->name, pStd_file)
        && fwrite_chars(pStudent->address, pStd_file)
        && fwrite_chars(pStudent->contact_number, pStd_file)
    ){
        puts("The new student was added successfully.\n");
    }else puts("Failed to add the student!\n");


    fflush(pStd_file);
    fflush(pStd_index_file);
}

static bool write_student_index(StudentIndex* pStdIndex, FILE* pStd_index_file){
    if(fwrite(pStdIndex, sizeof(StudentIndex), 1, pStd_index_file) != 1){
        puts("Failed to save student index.");

        return false;
    }

    return true;
}

static bool fwrite_chars(char* p, FILE* pStd_file){
    size_t len = strlen(p) + 1;

    return fwrite(&len, sizeof(len), 1, pStd_file) == 1
        && fwrite(p, sizeof(char), len, pStd_file) == len;
}
