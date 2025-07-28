#include "file_util.h"
#include "memory_util.h"

#include <stdbool.h>
#include <stdio.h>

bool set_ptr_file(FILE** ppFile, const char* file_path, const char* access_type){
    *ppFile = fopen(file_path, access_type);

    if(!(*ppFile)){
        printf("Failed to open %s.\n", file_path); 
        return false;
    }

    printf("Success to open %s\n", file_path);
    return true;
}

bool is_file_empty(FILE* pFile, const char* file_path){
    if(!is_allocated(pFile)){
        puts("Failed to know if the file is empty!");
        return true;
    }

    fseek(pFile, 0, SEEK_END);

    if(ftell(pFile) == 0){
        printf("The %s is empty!\n", file_path);
        return true;
    }

    return false;
}
