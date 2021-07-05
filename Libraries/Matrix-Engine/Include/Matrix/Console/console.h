#ifndef ___MTRX___CONSOLE_H
#define ___MTRX___CONSOLE_H

int matrix_printf(_In_z_ _Printf_format_string_ char const* const _Format, ...);

#ifdef ___MTRX_NOCONSOLEOUTPUT
#define MTRX_PRINTF(...)
#else
#define MTRX_PRINTF(...) \
matrix_printf(__VA_ARGS__)
#endif // !___MTRX_NOCONSOLEOUTPUT

#endif // !___MTRX___CONSOLE_H