#include "jl_platform_windows.h"


// http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe
static LPSTR jl_get_exec_path(char* (*allocfun)(const size_t size), void (*freefun)(), const int init_size) {
    DWORD size = init_size;
    for(;;) {
        //char* link = jl_heap->parent_path_alloc(size);
        LPSTR const path = allocfun(size);
        const DWORD res_size = GetModuleFileName(NULL, path, size);
        if(0 == res_size) jl_error("jl_get_exec_path: GetModuleFileName error");
        if(res_size < size) return path;
        freefun();
        size = size*2;
    }
}

char* jl_get_dir_path() {
    LPSTR const path = jl_get_exec_path(jl_heap->parent_path_alloc, jl_heap->parent_path_free, pow(2, 5));
    jl_strip_filename(path, '\\');
    return path;
}

void jl_exec_java(const char* javapath, const char* jarpath) {
//    printf("%s - %s\n", javapath, jarpath);
    // prepare command line string
    LPSTR cmd_string = jl_heap->cmd_string_alloc(strlen(javapath) + strlen(" -jar ") + strlen(jarpath) + 1); 
    strcat(cmd_string, javapath);
    strcat(cmd_string, " -jar ");
    strcat(cmd_string, jarpath);
    // prepare process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    const DWORD flags = DETACHED_PROCESS;
    // run process
    CreateProcess(NULL, cmd_string, NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
