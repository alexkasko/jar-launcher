#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "jl_common.h"

/**
 * This struct controls all heap memory allocation
 * There are 4 elements for each heap variable:
 *  - pointer to allocated memory
 *  - flag whether the memory was allocated
 *  - function to allocate memory, 'throws' error on repeated calls
 *  - function to free memory, ignores repeated calls
 *
 * 'st->free()' function frees all allocaed memory
 */
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

/**
 * Heap struct initializer, must be called from main on start
 */
extern void jl_heap_init();

/**
 * Pointer to global heap structure, all allocations must be done through it
 */
extern jl_Heap* jl_heap;
