#include <stdio.h>

void set_input(void* con, char* pattern, char* prompt);

void input_int(int* pInt, char* prompt){
    set_input(pInt, "%d", prompt);
}

void input_double(double* pDouble, char* prompt){
    set_input(pDouble, "%lf", prompt);
}

void set_input(void* con, char* pattern, char* prompt){
    while(1){
        printf("%s", prompt);

        if(scanf(pattern, con) == 1){
            while(getchar() != '\n');
            break;
        }

        printf("Numbers can only be input on this section!\n");
        while(getchar() != '\n');
    }
}
