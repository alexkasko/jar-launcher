#pragma once
#include <stdbool.h> 

typedef struct {                                                                                                       
    char* path;                                                                                                        
    bool path_allocated;                                                                                               
    char* (*path_alloc)(size_t size);                                                                                  
    void (*path_free)();                                                                                               
    
    void (*free)();                                                                                                    
} jl_Heap;  

extern void jl_heap_init();

extern jl_Heap* jl_heap;
