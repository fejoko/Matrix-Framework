#ifndef ___MTRX___CONSOLE_H
#define ___MTRX___CONSOLE_H

#include "Matrix/Pch/INTERNAL/PCH_stdio.h"

int matrix_printf(const char* format, ...);

#ifdef ___MTRX_NOCONSOLEOUTPUT
#define MTRX_PRINTF(...)
#else
#define MTRX_PRINTF(...) \
matrix_printf(__VA_ARGS__)
#endif // !___MTRX_NOCONSOLEOUTPUT

#endif // !___MTRX___CONSOLE_H