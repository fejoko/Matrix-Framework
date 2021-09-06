#ifndef ___MTRX___INTERNAL_RENDERER_ERRORS_H
#define ___MTRX___INTERNAL_RENDERER_ERRORS_H

#include "Matrix/Core/error.h"

//----------renderer errors----------
#define MTRX_ERROR_RENDERER_API_OUTOFBOUND \
MTRX_ERROR_EXIT("renderer_api reached undefined value", "MTRX000x001x000r");
//----------------------------------

#endif // !___MTRX___INTERNAL_RENDERER_ERRORS_H