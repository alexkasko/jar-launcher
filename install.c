#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "jl_heap.h"

#define JL_PATH_SEPARATOR '/'
//#define JL_JAVA_RELATIVE_PATH "jre/bin/java"
//#define JL_JAR_RELATIVE_PATH "foo/bar/install.jar"

static void jl_error(const char* message) {
    jl_heap->free();
    if(errno) perror(message);
    else printf("ERROR: %s\n", message); 
    exit(1);
}

// http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
// http://stackoverflow.com/q/9385386/314015
static char* jl_readlink(const char * path, const int init_size, const int spare_size) {
    long size = init_size;
    for(;;) {
        char* link = jl_heap->path_alloc(size);
        ssize_t res_size = readlink(path, link, size);
        if(res_size < 0) jl_error("jl_readlink: readlink error");
        if(res_size + spare_size + 1 < size) return link;
        jl_heap->path_free();
        size = size*2;
    }
}

static char* jl_get_exec_path(const int spare_size) {
    return jl_readlink("/proc/self/exe", pow(2, 5), spare_size);
}

static void jl_exec_java(const char* javapath, const char* jarname) {
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

    execl(javapath, "java", "-jar", jarname, NULL);
}

// http://stackoverflow.com/a/5711554/314015
static void jl_path_to_parent_dir(char* path) {
    char* lastSlash = strrchr(path, JL_PATH_SEPARATOR);
    if(!lastSlash) jl_error("cannot get parent dir");
    *(lastSlash + 1) = '\0';
}

int main() {
    // init heap
    jl_heap_init();
    // get executable file name
    char* path = jl_get_exec_path(strlen(JL_JAVA_RELATIVE_PATH));
    // strip executable file name
    jl_path_to_parent_dir(path);
    // append java path
    strcat(path, JL_JAVA_RELATIVE_PATH);
    printf("Launching java: '%s -jar %s'\n", path, JL_JAR_RELATIVE_PATH);
    // start child
    jl_exec_java(path, JL_JAR_RELATIVE_PATH);
    // free heap
    jl_heap->free();
    return 0;
}
