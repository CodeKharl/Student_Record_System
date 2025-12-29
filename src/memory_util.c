#include "memory_util.h"

#include <stdio.h>
#include <stdbool.h>

bool is_allocated(void* p){
    if(!p){
        puts("Memory allocation failed");

        return false;
    }
    
    return true;
}
