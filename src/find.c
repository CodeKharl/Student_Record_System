#include "student.h"
#include "sys_util.h"
#include "memory_util.h"

#include <stdio.h>
#include <string.h>

void student_find(FILE** pFile, FILE** pFile_index){
    unsigned long id;
    char buffer[256];
    StudentIndex pStd_index;
    Student* pStudent = new_student();

    if(!is_allocated(pStudent)) return;

    printf("Find Student (Cancel == %d)\n", SECTION_EXIT); 

    while((id = input_id()) != SECTION_EXIT){
        if(!set_stdIndex_by_id(&pStd_index, id, *pFile_index) 
            || !set_std_by_index(pStudent,  &pStd_index, *pFile)
        ){
            continue;
        }
        
        memset(buffer, 0, sizeof(buffer));

        if(!set_student_str(buffer, pStudent, STUDENT_LABELED_FORMAT)){
            puts("Failed to print the student info");
            continue;
        }

        printf("\n%s\n\n", buffer);
    }

    delete_student(pStudent);
    puts("Finding cancelled! Go back to main menu...\n");
}
