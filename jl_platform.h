#pragma once

#include <unistd.h>
#include <math.h>
#include "jl_common.h"
#include "jl_heap.h"

extern char* jl_get_dir_path();

extern void jl_exec_java(const char* javapath, const char* jarpath);
