#include "memory_util.h"
#include "student.h"
#include "input.h"
#include "add.h"
#include "find.h"
#include "drop.h"
#include "file_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SYS_FUNCS_RANGE 4

typedef enum{
    ADD,
    FIND,
    UPDATE,
    DROP,
    EXIT
}Menu;

void sys_start(
    void (*func[SYS_FUNCS_RANGE])(FILE*, FILE*), 
    FILE* pStd_file, 
    FILE* pStd_index_file
);

bool isRunning(
    void (*func[SYS_FUNCS_RANGE])(FILE*, FILE*), 
    FILE* pStd_file, 
    FILE* pStd_index_file
);

int main(){
    FILE* pStd_file;
    FILE* pStd_index_file;
    void (*func[SYS_FUNCS_RANGE])(FILE*, FILE*);

    func[ADD] = student_add;
    func[FIND] = student_find;
    func[DROP] = student_drop;

    if(set_ptr_file(&pStd_file, DATA_FILE_PATH, "ab+")
       && set_ptr_file(&pStd_index_file, DATA_FILE_PATH_INDEX, "ab+")
    ){
        puts("Files has been setup\n");
        sys_start(func, pStd_file, pStd_index_file);

        fclose(pStd_file);
        fclose(pStd_index_file);

        return 0;
    }

    puts("The system files failed to set!");

    return 1;
}

void sys_start(
    void (*func[SYS_FUNCS_RANGE])(FILE*, FILE*), 
    FILE* pStd_file, 
    FILE* pStd_index_file
){
    do{
        puts("--> Student Record System <--");
        printf("%d. Add Student\n", ADD);
        printf("%d. Find Student\n", FIND);
        printf("%d. Update Student\n", UPDATE);
        printf("%d. Drop Student\n", DROP);
        printf("%d. Exit\n", EXIT);
    }while(isRunning(func, pStd_file, pStd_index_file));
}

bool isRunning(
    void (*func[SYS_FUNCS_RANGE])(FILE*, FILE*), 
    FILE* pStd_file, 
    FILE* pStd_index_file
){
    int choice;

    while(1){
        choice = get_input_int("Enter your choice : ");
        
        if(choice < ADD || choice > EXIT){
            puts("Invalid input! Please enter valid choice");
            continue;
        }

        if(choice == EXIT){
            puts("System exits...");
            return false;
        }

        func[choice](pStd_file, pStd_index_file);
        return true;
    }
}

