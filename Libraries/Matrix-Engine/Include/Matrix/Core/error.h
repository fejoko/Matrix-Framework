#ifndef ___MTRX___ERROR_H
#define ___MTRX___ERROR_H

#include "Matrix/Pch/mtrxstdafx.h"

void matrix_error_exit(const char* what, const char* code, const char* FILE, const char* func, const int LINE);
void matrix_error_abort(const char* what, const char* code, const char* FILE, const char* func, const int LINE);

#define MTRX_ERROR_EXIT(what, code) \
matrix_error_exit(what, code, __FILE__, __func__, __LINE__);

#define MTRX_ERROR_ABORT(what, code) \
matrix_error_abort(what, code, __FILE__, __func__, __LINE__);

//----------general errors----------
#define MTRX_ERROR_MALLOC_FAILED \
MTRX_ERROR_EXIT("malloc failed", "MTRX000x001x001g");

#define MTRX_ERROR_CALLOC_FAILED \
MTRX_ERROR_EXIT("calloc failed", "MTRX000x001x002g");

#define MTRX_ERROR_REALLOC_FAILED \
MTRX_ERROR_EXIT("realloc failed", "MTRX000x001x003g");

#define MTRX_ERROR_UNEXPECTED_NULL \
MTRX_ERROR_EXIT("unexpected NULL", "MTRX000x002x000g");
//----------------------------------

#endif // !___MTRX___ERROR_H