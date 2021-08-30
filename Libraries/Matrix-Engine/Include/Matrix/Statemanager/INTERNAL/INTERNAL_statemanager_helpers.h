#ifndef ___MTRX___INTERNAL_STATEMANAGER_HELPERS_H
#define ___MTRX___INTERNAL_STATEMANAGER_HELPERS_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Statemanager Matrix_Statemanager;

void matrix_statemanager_log(const char* format, size_t state_index, Matrix_Statemanager* statemanager);

#endif // !___MTRX___INTERNAL_STATEMANAGER_HELPERS_H