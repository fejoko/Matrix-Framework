#ifndef ___MTRX___CONSOLE_H
#define ___MTRX___CONSOLE_H

int matrix_printf(const char* format, ...);

#ifdef ___MTRX_NOCONSOLEOUTPUT
#define MTRX_PRINTF(...)
#else
#define MTRX_PRINTF(...) \
matrix_printf(__VA_ARGS__)
#endif // !___MTRX_NOCONSOLEOUTPUT

#ifdef ___MTRX_NOCONSOLECOLOR
static const char* const MATRIX_CONSOLE_COLOR_RESET = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_RED = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_GREEN = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_YELLOW = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_BLUE = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_PURPLE = "";
static const char* const MATRIX_CONSOLE_COLOR_FG_CYAN = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_RED = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_GREEN = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_YELLOW = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_BLUE = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_PURPLE = "";
static const char* const MATRIX_CONSOLE_COLOR_BG_CYAN = "";
#else
static const char* const MATRIX_CONSOLE_COLOR_RESET = "\033[0m";
static const char* const MATRIX_CONSOLE_COLOR_FG_RED = "\033[31m";
static const char* const MATRIX_CONSOLE_COLOR_FG_GREEN = "\033[32m";
static const char* const MATRIX_CONSOLE_COLOR_FG_YELLOW = "\033[33m";
static const char* const MATRIX_CONSOLE_COLOR_FG_BLUE = "\033[34m";
static const char* const MATRIX_CONSOLE_COLOR_FG_PURPLE = "\033[35m";
static const char* const MATRIX_CONSOLE_COLOR_FG_CYAN = "\033[36m";
static const char* const MATRIX_CONSOLE_COLOR_BG_RED = "\033[41m";
static const char* const MATRIX_CONSOLE_COLOR_BG_GREEN = "\033[42m";
static const char* const MATRIX_CONSOLE_COLOR_BG_YELLOW = "\033[43m";
static const char* const MATRIX_CONSOLE_COLOR_BG_BLUE = "\033[44m";
static const char* const MATRIX_CONSOLE_COLOR_BG_PURPLE = "\033[45m";
static const char* const MATRIX_CONSOLE_COLOR_BG_CYAN = "\033[46m";
#endif // ___MTRX_NOCONSOLECOLOR

#endif // !___MTRX___CONSOLE_H