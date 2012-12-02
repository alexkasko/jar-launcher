#include "jl_common.h"

void jl_error(const char* message) {
    jl_heap->free();
    if(errno) perror(message);
    else printf("ERROR: %s\n", message);
    exit(1);
}  

// http://stackoverflow.com/a/5711554/314015
void jl_strip_filename(const char* path, const int separator) {
    char* lastSlash = strrchr(path, separator);
    if(!lastSlash) jl_error("cannot get parent dir");
    *(lastSlash + 1) = '\0';
}
