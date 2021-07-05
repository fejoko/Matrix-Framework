#include "Matrix/Console/console.h"

#include "Matrix/Pch/INTERNAL/PCH_stdio.h"

int matrix_printf(_In_z_ _Printf_format_string_ char const* const format, ...)
{
    int _Result;
    va_list _ArgList;
    __crt_va_start(_ArgList, format);
    _Result = _vfprintf_l(stdout, format, NULL, _ArgList);
    __crt_va_end(_ArgList);
    return _Result;
}