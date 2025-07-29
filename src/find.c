#include "student.h"
#include "sys_util.h"
#include "memory_util.h"
#include "student_util.h"

#include <stdio.h>

void student_find(FILE** pStd_file, FILE** pStd_index_file){
    unsigned long id;
    StudentIndex pStd_index;
    Student* pStudent = new_student();

    if(!is_allocated(pStudent)) return;

    printf("Find Student (Cancel == %d)\n", SECTION_EXIT); 

    while((id = input_id()) != SECTION_EXIT){
        if(!set_stdIndex_by_id(&pStd_index, id, *pStd_index_file) 
            || !set_std_by_index(pStudent,  &pStd_index, *pStd_file)
        ){
            continue;
        }
        
        printf("\n");
        print_student(pStudent, STUDENT_LABELED_FORMAT);
    }

    delete_student(pStudent);
    puts("Finding cancelled! Go back to main menu...\n");
}
