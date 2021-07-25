#include "Matrix/Console/console.h"

#include "Matrix/Pch/INTERNAL/PCH_stdarg.h"
#include "Matrix/Pch/INTERNAL/PCH_stdio.h"

int matrix_printf(const char* format, ...)
{
        va_list args;
        va_start(args, format);
        int result = vfprintf(stdout, format, args);
        va_end(args);
        return result;
}