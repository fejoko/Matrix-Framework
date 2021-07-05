#ifndef ___MTRX___INTERNAL_VECTOR_DATA_H
#define ___MTRX___INTERNAL_VECTOR_DATA_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Vector
{
	size_t element_size;
	size_t vector_capacity;
	char* vector_data;
} Matrix_Vector;

#endif // !___MTRX___INTERNAL_VECTOR_DATA_H