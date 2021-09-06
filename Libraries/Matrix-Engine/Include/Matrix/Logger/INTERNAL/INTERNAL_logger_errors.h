#ifndef ___MTRX___INTERNAL_LOGGER_ERRORS_H
#define ___MTRX___INTERNAL_LOGGER_ERRORS_H

#include "Matrix/Core/error.h"

//----------logger errors----------
#define MTRX_ERROR_LOGGER_LEVEL_OUTOFBOUND \
MTRX_ERROR_EXIT("logger_level reached undefined value", "MTRX000x001x000l");
//----------------------------------

#endif // !___MTRX___INTERNAL_LOGGER_ERRORS_H