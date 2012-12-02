#pragma once
#include <errno.h>
#include <stdio.h>
#include "jl_heap.h"

extern void jl_error(const char* message);
extern void jl_strip_filename(const char* path, const int separator);
