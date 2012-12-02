#include <stdlib.h>
#include <string.h>
#include "jl_heap.h"


jl_Heap* jl_heap;

// path functions

static char* path_alloc(size_t size) {
    jl_heap->path = malloc(size);
    jl_heap->path_allocated = true;
    memset(jl_heap->path, 0, size);
    return jl_heap->path;
}

static void path_free() {
    if(!jl_heap->path_allocated) return;
    free(jl_heap->path);
    jl_heap->path_allocated = false;
}

// main heap functions

static void heap_free() {
    jl_heap->path_free();
    free(jl_heap);
}

extern void jl_heap_init() {
    jl_heap = malloc(sizeof(jl_Heap));
    jl_heap->path_alloc = path_alloc;
    jl_heap->path_free = path_free;
    jl_heap->path_allocated = false;
    jl_heap->free = heap_free;
}
