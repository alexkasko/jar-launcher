#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "jl_common.h"
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
// cmd_string functions
static char* cmd_string_alloc(const size_t size) {
    if(jl_heap->cmd_string_allocated) jl_error("cmd_string_alloc: already allocated");
    jl_heap->cmd_string = malloc(size);
    jl_heap->cmd_string_allocated = true;
    memset(jl_heap->cmd_string, 0, size);
    return jl_heap->cmd_string;
}
static void cmd_string_free() {
    if(!jl_heap->cmd_string_allocated) return;
    free(jl_heap->cmd_string);
    jl_heap->cmd_string_allocated = false;
}

// main heap functions

static void heap_free() {
    jl_heap->parent_path_free();
    jl_heap->java_path_free();
    jl_heap->jar_path_free();
    jl_heap->cmd_string_free();
    free(jl_heap);
}

void jl_heap_init() {
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
    jl_heap->cmd_string_alloc = cmd_string_alloc;
    jl_heap->cmd_string_free = cmd_string_free;
    jl_heap->cmd_string_allocated = false;
    jl_heap->free = heap_free;
}
