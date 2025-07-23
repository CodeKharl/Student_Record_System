#include "student.h"
#include "input.h"
#include "sys_util.h"

#include <stdio.h>

void student_find(FILE* pFile){
    unsigned long id;

    printf("Find Student (Cancel == %d)\n", SECTION_EXIT); 

    while((id = input_id()) != SECTION_EXIT){
    }

    puts("Finding cancelled! Go back to main menu...");
}
