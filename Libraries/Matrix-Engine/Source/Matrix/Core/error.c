#include "Matrix/Core/error.h"

#include "Matrix/Console/console.h"
#include "Matrix/Core/configuration.h"

void matrix_error_exit(const char* what, const char* code, const char* FILE, const char* func, const int LINE)
{
	if (MTRX_DEBUG_IS || MTRX_MINSIZEREL_IS)
	{
		MTRX_PRINTF("----------\nexit has been called\n\nfile:\t%s\nfunc:\t%s\nline:\t%i\ncode:\t%s\nwhat:\t%s\n\nsee documentation for more information\n\nif you not are a developer please contact same\n----------\n", FILE, func, LINE, code, what);
	}
	else
	{
		MTRX_PRINTF("exit has been called\n");
	}

	exit(-1);
}

void matrix_error_abort(const char* what, const char* code, const char* FILE, const char* func, const int LINE)
{
	if (MTRX_DEBUG_IS || MTRX_MINSIZEREL_IS)
	{
		MTRX_PRINTF("----------\abort has been called\n\nfile:\t%s\nfunc:\t%s\nline:\t%i\nwhat:\t%s\n\nsee documentation for more information\n\nif you not are a developer please contact same\n----------\n", FILE, func, LINE, what);
	}
	else
	{
		MTRX_PRINTF("abort has been called\n");
	}

	exit(-1);
}