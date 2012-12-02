#include "jl_heap.h"

jl_Heap* jl_heap;

// parent_path functions
static char* parent_path_alloc(const size_t size) {
    if(jl_heap->parent_path_allocated) jl_error("parent_path_alloc: already allocated");
    jl_heap->parent_path = malloc(size);
    jl_heap->parent_path_allocated = true;
    memset(jl_heap->parent_path, 0, size);
    return jl_heap->parent_path;
}
static void parent_path_free() {
    if(!jl_heap->parent_path_allocated) return;
    free(jl_heap->parent_path);
    jl_heap->parent_path_allocated = false;
}

// java_path functions
static char* java_path_alloc(const size_t size) {
    if(jl_heap->java_path_allocated) jl_error("java_path_alloc: already allocated");
    jl_heap->java_path = malloc(size);
    jl_heap->java_path_allocated = true;
    memset(jl_heap->java_path, 0, size);
    return jl_heap->java_path;
}
static void java_path_free() {
    if(!jl_heap->java_path_allocated) return;
    free(jl_heap->java_path);
    jl_heap->java_path_allocated = false;
}

// jar_path functions
static char* jar_path_alloc(const size_t size) {
    if(jl_heap->jar_path_allocated) jl_error("jar_path_alloc: already allocated");
    jl_heap->jar_path = malloc(size);
    jl_heap->jar_path_allocated = true;
    memset(jl_heap->jar_path, 0, size);
    return jl_heap->jar_path;
}
static void jar_path_free() {
    if(!jl_heap->jar_path_allocated) return;
    free(jl_heap->jar_path);
    jl_heap->jar_path_allocated = false;
}

// main heap functions

static void heap_free() {
    jl_heap->parent_path_free();
    jl_heap->java_path_free();
    jl_heap->jar_path_free();
    free(jl_heap);
}

extern void jl_heap_init() {
    jl_heap = malloc(sizeof(jl_Heap));
    jl_heap->parent_path_alloc = parent_path_alloc;
    jl_heap->parent_path_free = parent_path_free;
    jl_heap->parent_path_allocated = false;
    jl_heap->java_path_alloc = java_path_alloc;
    jl_heap->java_path_free = java_path_free;
    jl_heap->java_path_allocated = false;
    jl_heap->jar_path_alloc = jar_path_alloc;
    jl_heap->jar_path_free = jar_path_free;
    jl_heap->jar_path_allocated = false;
    jl_heap->free = heap_free;
}
