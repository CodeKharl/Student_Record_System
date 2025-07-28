#include "add.h"
#include "student.h"
#include "memory_util.h"
#include "input.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static void set_input_student(Student* pStudent, FILE* pFile, FILE* pFile_index);
static unsigned long new_std_id(FILE* pFile, FILE* pFile_index);
static bool is_confirm(Student* pStudent);
static void write_student(FILE* pFile, FILE* pFile_index, Student* pStudent);
static bool write_student_index(StudentIndex* pStdIndex, FILE* pFile_index);
static bool fwrite_chars(char* p, FILE* pFile);

void student_add(FILE** pFile, FILE** pFile_index){
    puts("\nAdd Student");

    Student* pStudent = new_student();
    if(!is_allocated(pStudent)) return;

    set_input_student(pStudent, *pFile, *pFile_index);

    if(is_confirm(pStudent)){
        write_student(*pFile, *pFile_index, pStudent);
    }
    
    delete_student(pStudent);
}

static void set_input_student(Student* pStudent, FILE* pFile, FILE* pFile_index){
    pStudent->name = input_name(MAX_NAME_SIZE);
    pStudent->age = input_age();
    pStudent->sex = input_sex();
    pStudent->address = input_address(MAX_ADDRESS_SIZE);
    pStudent->contact_number = input_contact_num(MAX_CONTACT_NUM_SIZE);
    pStudent->id = new_std_id(pFile, pFile_index);
}

static unsigned long new_std_id(FILE* pFile, FILE* pFile_index){
    StudentIndex last_stdIndex;

    puts("\nCreating new ID...");

    if(set_last_stdIndex(&last_stdIndex, pFile_index)){
        return last_stdIndex.id + 1;
    }

    puts("First student to record.");
    
    return 1;
}

static bool is_confirm(Student* pStudent){
    char choice;
    char buffer[256];

    memset(buffer, 0, sizeof(buffer));

    if(!set_student_str(buffer, pStudent, STUDENT_LABELED_FORMAT)){
        puts("\nFailed to display the student info.");
    }else printf("\n%s\n", buffer);

    while(1){
        choice = get_input_char("\nContinue to add this student (Y/N): ");

        switch(toupper(choice)){
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

static void write_student(FILE* pFile, FILE* pFile_index, Student* pStudent){
    StudentIndex stdIndex;

    stdIndex.id = pStudent->id;
    stdIndex.offset = ftell(pFile);

    if(!write_student_index(&stdIndex, pFile_index)){
        return;
    }

    fwrite(&pStudent->id, sizeof(pStudent->id), 1, pFile);
    fwrite(&pStudent->age, sizeof(pStudent->age), 1, pFile);
    fwrite(&pStudent->sex, sizeof(pStudent->sex), 1, pFile);
    
    if(fwrite_chars(pStudent->name, pFile)
        && fwrite_chars(pStudent->address, pFile)
        && fwrite_chars(pStudent->contact_number, pFile)
    ){
        puts("The new student was added successfully!\n");
    }else puts("Failed to add the student\n");


    fflush(pFile);
    fflush(pFile_index);
}

static bool write_student_index(StudentIndex* pStdIndex, FILE* pFile_index){
    if(fwrite(pStdIndex, sizeof(StudentIndex), 1, pFile_index) != 1){
        puts("Failed to save student index.");

        return false;
    }

    return true;
}

static bool fwrite_chars(char* p, FILE* pFile){
    size_t len = strlen(p) + 1;

    return fwrite(&len, sizeof(len), 1, pFile) == 1
        && fwrite(p, sizeof(char), len, pFile) == len;
}
