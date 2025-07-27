#include "drop.h"
#include "student.h"
#include "input.h"
#include "student.h"
#include "sys_util.h"

#include <stdio.h>
#include <stdbool.h>

static bool set_std_index(FILE* pStd_index_file, const unsigned long id);

void student_drop(FILE *pStd_file, FILE *pStd_index_file){
    unsigned long id;
    StudentIndex std_index;

    printf("\nDrop Student (Back == %d)\n", SECTION_EXIT);

    while((id = input_id()) != SECTION_EXIT){
    }

    puts("Drop student ended! Go back to main menu...\n");
}

static bool set_std_index(FILE* pStd_index_file, const unsigned long id);



