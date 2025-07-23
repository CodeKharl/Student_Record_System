#include "memory_util.h"
#include "student.h"
#include "input.h"
#include "add.h"
#include "find.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_FILE_PATH "data/student.dat"

typedef enum{
    ADD = 1,
    FIND,
    UPDATE,
    DROP,
    EXIT
}Menu;

void sys_start(FILE* pFile);
bool isRunning(FILE* pFile);

int main(){
    FILE* pFile = fopen(DATA_FILE_PATH, "ab+");

    if(is_allocated(pFile)){
        sys_start(pFile);
        fclose(pFile);

        return 0;
    }

    printf("The %s cannot be open! The system will not work.", DATA_FILE_PATH);

    return 1;
}

void sys_start(FILE* pFile){
    do{
        puts("--> Student Record System <--");
        printf("%d. Add Student\n", ADD);
        printf("%d. Find Student\n", FIND);
        printf("%d. Update Student\n", UPDATE);
        printf("%d. Drop Student\n", DROP);
        printf("%d. Exit\n", EXIT);
    }while(isRunning(pFile)); 
}

bool isRunning(FILE* pFile){
    int choice;

    while(1){
        choice = get_input_int("Enter your choice : ");

        switch(choice){
            case ADD:
                student_add(pFile);
                return true;
            case FIND:
                student_find(pFile);
                return true;
            case UPDATE:
                return true;
            case DROP:
                return true;
            case EXIT:
                puts("System Exits...");
                return false;
            default:
                puts("Invalid input! Please enter valid choice");
        }
    }
}

