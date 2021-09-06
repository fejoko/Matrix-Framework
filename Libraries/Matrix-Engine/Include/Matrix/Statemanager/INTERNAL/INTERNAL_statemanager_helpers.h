#ifndef ___MTRX___INTERNAL_STATEMANAGER_HELPERS_H
#define ___MTRX___INTERNAL_STATEMANAGER_HELPERS_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Statemanager Matrix_Statemanager;

void matrix_statemanager_log(const char* format, size_t state_index, Matrix_Statemanager* statemanager);

#ifdef ___MTRX_NOLOG
#define MTRX_STATEMANAGER_LOG(format, state_index, statemanager)
#else
#define MTRX_STATEMANAGER_LOG(format, state_index, statemanager) \
matrix_statemanager_log(format, state_index, statemanager)
#endif // !___MTRX_NOLOG

#endif // !___MTRX___INTERNAL_STATEMANAGER_HELPERS_H