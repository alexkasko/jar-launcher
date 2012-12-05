#pragma once

/** 
 * Frees memory using jl_heap, reports error message to stdout, shutdowns program
 */
extern void jl_error(const char* message);

/**
 * Remove filename from file system path leaving directory path
 */
extern void jl_strip_filename(const char* path, const int separator);
