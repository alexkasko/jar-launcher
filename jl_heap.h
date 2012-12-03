#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "jl_common.h"

typedef struct {                                                                                                       
    // parent absolute path
    char* parent_path;
    bool parent_path_allocated;
    char* (*parent_path_alloc)(size_t size);
    void (*parent_path_free)();
    // java executable relative path
    char* java_path;
    bool java_path_allocated;
    char* (*java_path_alloc)(size_t size);
    void (*java_path_free)();
    // jar file relative path
    char* jar_path;
    bool jar_path_allocated;
    char* (*jar_path_alloc)(size_t size);
    void (*jar_path_free)();
    // full command line string
    char* cmd_string;
    bool cmd_string_allocated;
    char* (*cmd_string_alloc)(size_t size);
    void (*cmd_string_free)();
    
    void (*free)();
} jl_Heap;  

extern void jl_heap_init();

extern jl_Heap* jl_heap;
