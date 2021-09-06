#ifndef ___MTRX___INTERNAL_WINDOW_ERRORS_H
#define ___MTRX___INTERNAL_WINDOW_ERRORS_H

#include "Matrix/Core/error.h"

//----------window errors----------
#define MTRX_ERROR_WINDOW_API_OUTOFBOUND \
MTRX_ERROR_EXIT("window_api reached undefined value", "MTRX000x001x000w");
//----------------------------------

#endif // !___MTRX___INTERNAL_WINDOW_ERRORS_H