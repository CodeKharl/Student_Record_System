#include "student_util.h"
#include "student.h"
#include "input.h"
#include "memory_util.h"
#include "file_util.h"

#include <stdlib.h>

static bool set_ptr_student(Student* pStudent, const StudentIndex* pStd_index, FILE* pStd_file);
static bool set_ptr_stdIndex(StudentIndex* pStd_index, const long offset, const int whence, FILE* pStd_index_file);
static bool set_char_ptr_std(char** ppStr, FILE* pStd_file);

void print_student(Student *pStudent, const char *format){
    if(!pStudent){
        puts("Error: Student pointer is null");
        return;
    }

    if(format != STUDENT_LABELED_FORMAT
        && format != STUDENT_DEFAULT_FORMAT
    ){
        puts("Error: The format cannot be implement");
        return;
    }

    printf(
        format, 
        pStudent->id, 
        pStudent->name, 
        pStudent->age, 
        pStudent->sex, 
        pStudent->address, 
        pStudent->contact_number
    );

    printf("\n");
}

bool set_stdIndex_by_id(StudentIndex* pStd_index, const unsigned long id, FILE* pStd_file_index){
    unsigned long last_std_id;
    long offset;

    if(!is_allocated(pStd_index) 
        || !set_last_stdIndex(pStd_index, pStd_file_index)
    ){
        puts("Failed to get student index");
        return false;
    }

    last_std_id = pStd_index->id;
    offset = (id - 1)  * (sizeof(StudentIndex));

    if(id <= last_std_id && (id == last_std_id
        || set_ptr_stdIndex(pStd_index, offset, SEEK_SET, pStd_file_index))
    ){
        puts("Student index found!");
        return true;
    }

    puts("Student not found!");

    return false;
}

bool set_last_stdIndex(StudentIndex* pStd_index, FILE* pStd_file_index){
    if(set_ptr_stdIndex(pStd_index, -sizeof(StudentIndex), SEEK_END, pStd_file_index)){
        puts("Last student index found!");
        return true;
    }

    puts("Failed to get last student index");
    return false;
}

static bool set_ptr_stdIndex(StudentIndex* pStd_index, const long offset, const int whence, FILE* pStd_file_index){
    fseek(pStd_file_index, 0, SEEK_END);

    if(is_file_empty(pStd_file_index, DATA_FILE_INDEX_PATH)){
        return false;
    }

    fseek(pStd_file_index, offset, whence);

    return fread(pStd_index, sizeof(StudentIndex), 1, pStd_file_index) == 1;
}

bool set_std_by_index(Student* pStudent, const StudentIndex* pStd_index, FILE* pStd_file){
    if(pStudent && set_ptr_student(pStudent, pStd_index, pStd_file)){
        puts("Student info found!");
        return true;
    }

    puts("Student info not found!");

    return false;
}

static bool set_ptr_student(Student* pStudent, const StudentIndex* pStd_index, FILE* pStd_file){
    fseek(pStd_file, 0, SEEK_END);

    if(is_file_empty(pStd_file, DATA_FILE_PATH)){
        return false;
    }

    fseek(pStd_file, pStd_index->offset, SEEK_SET);

    fread(&pStudent->id, sizeof(pStudent->id), 1, pStd_file);
    fread(&pStudent->age, sizeof(pStudent->age), 1, pStd_file);
    fread(&pStudent->sex, sizeof(pStudent->sex), 1, pStd_file);

    return set_char_ptr_std(&pStudent->name, pStd_file)
        && set_char_ptr_std(&pStudent->address, pStd_file)
        && set_char_ptr_std(&pStudent->contact_number, pStd_file);
}

static bool set_char_ptr_std(char** pStr, FILE* pStd_file){
    size_t len;

    if(fread(&len, sizeof(len), 1, pStd_file) != 1){
        return false;
    }

    *pStr = malloc(len);

    return is_allocated(*pStr) 
        && (fread(*pStr, sizeof(char), len, pStd_file) == len);
}

unsigned long input_id(){
    long id;

    while((id = get_input_long("Enter student id : ")) < 0){
        puts("ID number too low!");
    }

    return id;
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
