#include <string.h>
#include <stdio.h>
#include "jl_common.h"
#include "jl_heap.h"
#include "jl_platform.h"

// see these variables in Makefile 
//#define JL_JAVA_RELATIVE_PATH "jre/bin/java"
//#define JL_JAR_RELATIVE_PATH "path/to/launcher.jar"

/**
 * Executes JAR file with precompiled paths (relative to executable)
 * startting JVM in separate process and exiting this one
 */
int main() {
    jl_heap_init();
    // parent path
    char* parent_path = jl_get_dir_path();
    int parent_len = strlen(parent_path);
    // java path
    char* java_path = jl_heap->java_path_alloc(parent_len + strlen(JL_JAVA_RELATIVE_PATH) + 1);
    strncpy(java_path, parent_path, parent_len);
    strcat(java_path, JL_JAVA_RELATIVE_PATH);
    // jar path
    char* jar_path = jl_heap->jar_path_alloc(parent_len + strlen(JL_JAR_RELATIVE_PATH) + 1);
    strncpy(jar_path, parent_path, parent_len);
    strcat(jar_path, JL_JAR_RELATIVE_PATH);
    // start child
    printf("Launching java: '%s -jar %s'\n", java_path, jar_path);
    jl_exec_java(java_path, jar_path);
    // free heap
    jl_heap->free();
    return 0;
}
