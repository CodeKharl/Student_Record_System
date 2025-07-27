#include "file_util.h"

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
