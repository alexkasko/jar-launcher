#pragma once

/**
 * Must return file system path of current executable using platform-specific API
 */
extern char* jl_get_dir_path();

/**
 * Must launch external java process with provided paths using
 * platform specific API (fork/exec or CreateProcess)
 */
extern void jl_exec_java(const char* javapath, const char* jarpath);
