#include "Matrix/Core/error.h"

#include "Matrix/Console/console.h"
#include "Matrix/Core/configuration.h"

void matrix_error_exit(const char* what, const char* code, const char* FILE, const char* func, const int LINE, const char* DATE, const char* TIME)
{
	if (MTRX_DEBUG_IS || MTRX_MINSIZEREL_IS)
	{
		MTRX_PRINTF("----------\nexit has been called\n\nfile:\t%s\nfunc:\t%s\nline:\t%i\ncode:\t%s\nwhat:\t%s\ndate:\t%s\ntime:\t%s\n\nsee documentation for more information\n\nif you not are a developer please contact same\n----------\n", strstr(FILE, "Matrix-Framework"), func, LINE, code, what, DATE, TIME);
	}
	else
	{
		MTRX_PRINTF("exit has been called: %s\n", code);
	}

	exit(-1);
}

void matrix_error_abort(const char* what, const char* code, const char* FILE, const char* func, const int LINE, const char* DATE, const char* TIME)
{
	if (MTRX_DEBUG_IS || MTRX_MINSIZEREL_IS)
	{
		MTRX_PRINTF("----------\abort has been called\n\nfile:\t%s\nfunc:\t%s\nline:\t%i\nwhat:\t%s\ndate:\t%s\ntime:\t%s\n\nsee documentation for more information\n\nif you not are a developer please contact same\n----------\n", strstr(FILE, "Matrix-Framework"), func, LINE, what, DATE, TIME);
	}
	else
	{
		MTRX_PRINTF("abort has been called: %s\n", code);
	}

	exit(-1);
}