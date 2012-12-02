#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "jl_common.h"
#include "jl_heap.h"

#define JL_PATH_SEPARATOR '/'
//#define JL_JAVA_RELATIVE_PATH "jre/bin/java"
//#define JL_JAR_RELATIVE_PATH "foo/bar/install.jar"


// http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
// http://stackoverflow.com/q/9385386/314015
static char* jl_readlink(const char * path, char* (*allocfun)(const size_t size), void (*freefun)(), const int init_size) {
    long size = init_size;
    for(;;) {
        //char* link = jl_heap->parent_path_alloc(size);
        char* link = allocfun(size);
        ssize_t res_size = readlink(path, link, size);
        if(res_size < 0) jl_error("jl_readlink: readlink error");
        if(res_size < size) return link;
        freefun();
        size = size*2;
    }
}

// http://stackoverflow.com/a/5711554/314015
static void jl_strip_filename(char* path) {
    char* lastSlash = strrchr(path, JL_PATH_SEPARATOR);
    if(!lastSlash) jl_error("cannot get parent dir");
    *(lastSlash + 1) = '\0';
}

static char* jl_get_dir_path() {
    char* path = jl_readlink("/proc/self/exe", jl_heap->parent_path_alloc, jl_heap->parent_path_free, pow(2, 5));
    jl_strip_filename(path);
    return path;
}

static void jl_exec_java(const char* javapath, const char* jarpath) {
    pid_t pid = fork();
    if(pid < 0) {
        jl_error("fork error");
    }
    if(pid > 0) { // parent exit
        jl_heap->free();
        exit(0);
    }
    pid_t sid = setsid();
    if(sid < 0) {
        jl_error("setsid error");
    }

    // java won't run without std*
    //fclose(stdin);
    //fclose(stdout);
    //fclose(stderr);

    execl(javapath, "java", "-jar", jarpath, NULL);
}


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
