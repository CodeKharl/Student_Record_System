#include "memory_util.h"

#include <stdio.h>
#include <stdbool.h>

bool is_allocated(void* p){
    if(!p){
        printf("Memory allocation failed");

        return false;
    }
    
    return true;
}
