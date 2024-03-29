#ifndef ___MTRX___INTERNAL_VECTOR_ERRORS_H
#define ___MTRX___INTERNAL_VECTOR_ERRORS_H

#include "Matrix/Core/error.h"

//----------vector errors----------
#define MTRX_ERROR_VECTOR_INVALID_ELEMENT_SIZE \
MTRX_ERROR_EXIT("invalid vector_element_size", "MTRX000x001x000v");

#define MTRX_ERROR_VECTOR_INVALID_CAPACITY \
MTRX_ERROR_EXIT("invalid vector_capacity", "MTRX000x002x000v");

#define MTRX_ERROR_VECTOR_INVALID_INDEX \
MTRX_ERROR_EXIT("invalid vector_index", "MTRX000x003x000v");
//----------------------------------

#endif // !___MTRX___INTERNAL_VECTOR_ERRORS_H