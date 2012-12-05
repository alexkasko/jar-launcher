#include <unistd.h>
#include <math.h>
#include <mach-o/dyld.h>
#include "jl_common.h"
#include "jl_heap.h"
#include "jl_platform.h"


// http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
static char* jl_get_exec_path(char* (*allocfun)(const size_t size), void (*freefun)(), const int init_size) {
    uint32_t size = init_size;
    char* path = allocfun(size);
    int res = _NSGetExecutablePath(path, &size);
    if(0 == res) return path;
    if(-1 != res) jl_error("jl_get_exec_path: _NSGetExecutablePath error");
    freefun();
    path = allocfun(size);
    res = _NSGetExecutablePath(path, &size);
    if(0 != res) jl_error("jl_get_exec_path: _NSGetExecutablePath secondary error");
    return path;
}


char* jl_get_dir_path() {
    char* path = jl_get_exec_path(jl_heap->parent_path_alloc, jl_heap->parent_path_free, pow(2, 5));
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
