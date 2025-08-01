#include "drop.h"
#include "memory_util.h"
#include "student.h"
#include "student.h"
#include "sys_util.h"
#include "file_util.h"
#include "input.h"
#include "student_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

static bool delete_std_index(
    const unsigned long id, 
    FILE* pStd_index_file,
    FILE* pStd_file
);

static bool write_temp_file(
    const unsigned long id, 
    FILE* pTemp_file, 
    FILE* pStd_index_file, 
    FILE* pStd_file
);

static bool is_drop_confirm(StudentIndex* pStd_index, FILE* pStd_file);

void student_drop(FILE** pStd_file, FILE** pStd_index_file){
    unsigned long id;

    printf("\nDrop Student (Back == %d)\n", SECTION_EXIT);

    while((id = input_id()) != SECTION_EXIT){
        if(delete_std_index(id, *pStd_index_file, *pStd_file)){
            puts("Student drop success!");

            fclose(*pStd_index_file);
            *pStd_index_file = fopen(DATA_FILE_INDEX_PATH, "ab+");

            break;
        }
    }

    puts("Drop student ended! Go back to main menu...\n");
}

static bool delete_std_index(
    const unsigned long id, 
    FILE* pStd_index_file,
    FILE* pStd_file
){
    FILE* pTemp_file = fopen(DATA_TEMP_FILE_PATH, "ab");

    if(!is_allocated(pTemp_file) 
        || is_file_empty(pStd_index_file, DATA_FILE_INDEX_PATH)
        || !write_temp_file(id, pTemp_file, pStd_index_file, pStd_file)
    ){
        puts("Failed to drop the student");
        
        fclose(pTemp_file);
        remove(DATA_TEMP_FILE_PATH);

        return false;       
    }

    fclose(pTemp_file);

    remove(DATA_FILE_INDEX_PATH);
    rename(DATA_TEMP_FILE_PATH, DATA_FILE_INDEX_PATH); 

    return true;
}

static bool write_temp_file(
    const unsigned long id, 
    FILE* pTemp_file, 
    FILE* pStd_index_file, 
    FILE* pStd_file
){
    StudentIndex std_index_temp;
    bool is_found = false;

    fseek(pStd_index_file, 0, SEEK_SET);

    while(fread(&std_index_temp, sizeof(std_index_temp), 1, pStd_index_file) == 1){
        if(std_index_temp.id == id && is_drop_confirm(&std_index_temp, pStd_file)){
            is_found = true;
            continue;
        }

        if(fwrite(&std_index_temp, sizeof(std_index_temp), 1, pTemp_file) != 1){
            puts("Failed to write student indexs in the temp file");
            return false;
        }
    }

    if(!is_found){
        puts("Student not found!");
        return false;
    }

    return true;
}

static bool is_drop_confirm(StudentIndex* pStd_index, FILE* pStd_file){
    char choice;
    Student* pStudent = new_student();

    if(set_std_by_index(pStudent, pStd_index, pStd_file)){
        printf("\n");
        print_student(pStudent, STUDENT_LABELED_FORMAT);
    }else puts("Failed to display student info");

    delete_student(pStudent);

    while(1){
        choice = get_input_char("Do you still want to drop this student (Y/N): ");

        switch(toupper(choice)){
            case YES:
                return true;
            case NO:
                return false;
            default:
                puts("Invalid input! Please try again.");
                break;
        }
    }
}
