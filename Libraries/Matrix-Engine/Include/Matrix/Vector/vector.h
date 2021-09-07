#ifndef ___MTRX___VECTOR_H
#define ___MTRX___VECTOR_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Vector Matrix_Vector;

Matrix_Vector* matrix_vector_construct(const size_t element_size, const size_t vector_capacity);
void matrix_vector_destruct(Matrix_Vector** const vector);

char* matrix_vector_at(const size_t index, Matrix_Vector* const vector);
char* matrix_vector_front(Matrix_Vector* const vector);
char* matrix_vector_back(Matrix_Vector* const vector);
char* matrix_vector_data(Matrix_Vector* const vector);

size_t matrix_vector_capacity(Matrix_Vector* const vector);

void matrix_vector_clear(Matrix_Vector* const vector);
//void matrix_vector_insert(size_t index, char* element, Matrix_Vector* vector);
//void matrix_vector_emplace(size_t index, char* element, Matrix_Vector* vector);
void matrix_vector_push_back(char* const element, Matrix_Vector* const vector); //element must be pointer to stack allocated 
//void matrix_vector_emplace_back(char* element, Matrix_Vector* vector);
void matrix_vector_pop_back(Matrix_Vector* const vector);
void matrix_vector_resize(const size_t capacity, Matrix_Vector* const vector);
//void matrix_vector_swap(Matrix_Vector* vector1, Matrix_Vector* vector2);

//void matrix_vector_copy(Matrix_Vector* source, Matrix_Vector* destination);
//void matrix_vector_copy_assign(Matrix_Vector* source, Matrix_Vector* destination);
//Matrix_Vector* matrix_vector_move_construct(Matrix_Vector* source);
//void matrix_vector_move_assign(Matrix_Vector* source, Matrix_Vector* destination);

#define MTRX_VECTOR_ELEMENT(element) \
(char*)&element

#define MTRX_VECTOR_AT_AS(type, index, vector) \
(*(type*)matrix_vector_at(index, vector))

#define MTRX_VECTOR_DATA_AS(type, vector) \
(*(type*)matrix_vector_data(vector))

#endif // !___MTRX___VECTOR_H