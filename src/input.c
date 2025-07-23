#include "memory_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_input(void* con, const char* pattern, char* val_type, const char* prompt){
    while(1){
        printf("%s", prompt);

        if(scanf(pattern, con) == 1){
            while(getchar() != '\n');
            break;
        }

        printf("Invalid input! (must be a %s).\n", val_type);
        while(getchar() != '\n');
    }
}

int get_input_int(const char* prompt){
    int num;
    set_input(&num, "%d", "number", prompt);

    return num;
}

double get_input_double(const char* prompt){
    double num;
    set_input(&num, "%lf", "decimal number", prompt);
    
    return num;
}

char get_input_char(char* prompt){
    char input;
    set_input(&input, "%c", "character", prompt);

    return input;
}

char* get_input_str(const size_t size, const char* prompt){
    char* pStr = malloc(size);

    if(!is_allocated(pStr)){
        return NULL;
    }

    while(1){
        printf("%s", prompt);

        if(fgets(pStr, size, stdin) != NULL){
            *(pStr + strcspn(pStr, "\n")) = '\0'; 

            if(strlen(pStr) > 0) return pStr;
        }

        puts("Theres no input!");
    }
}
