#include "jl_common.h"

extern void jl_error(const char* message) {
    jl_heap->free();
    if(errno) perror(message);
    else printf("ERROR: %s\n", message);
    exit(1);
}  
