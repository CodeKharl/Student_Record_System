
#include "student.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
    ADD = 1,
    FIND,
    UPDATE,
    DROP,
    EXIT
}Menu;

bool isRunning();

int main(){
    /* do{
        printf("--> Student Record System <--\n");
        printf("%d. Add Student\n", ADD);
        printf("%d. Find Student\n", FIND);
        printf("%d. Update Student\n", UPDATE);
        printf("%d. Drop Student\n", DROP);
        printf("%d. Exit\n", EXIT);
    }while(isRunning());

    */

    Student* std = malloc(sizeof(Student));
    std->id = 24211;
    std->name = "Kharl Denzell";
    std->age = 19;
    std->sex = MALE;
    std->address = "Holy Friday, Mallig, Isabela";
    std->phone_number = "09605326220";

    char* buffer = malloc(256);

    student_str(buffer, 256, std);
    printf("%s\n", buffer);

    free(buffer);
    free(std);

    return 0;
}

bool isRunning(){
    int choice;

    while(1){
        input_int(&choice, "Enter your choice : ");

        switch(choice){
            case ADD:
                return true;
            case FIND:
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

