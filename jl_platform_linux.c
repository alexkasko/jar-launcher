#include "jl_platform_linux.h"

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

char* jl_get_dir_path() {
    char* path = jl_readlink("/proc/self/exe", jl_heap->parent_path_alloc, jl_heap->parent_path_free, pow(2, 5));
    jl_strip_filename(path, '/');
    return path;
}

void jl_exec_java(const char* javapath, const char* jarpath) {
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
