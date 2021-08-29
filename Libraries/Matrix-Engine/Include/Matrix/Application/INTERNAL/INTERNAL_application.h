#ifndef ___MTRX___INTERNAL_APPLICATION_H
#define ___MTRX___INTERNAL_APPLICATION_H

#include "Matrix/Pch/mtrxstdafx.h"

#include "Matrix/Application/application.h"

typedef struct Matrix_Application Matrix_Application;

Matrix_Application matrix_applicatione_construct();
void matrix_application_destruct(Matrix_Application* const application);

#endif // !___MTRX___INTERNAL_APPLICATION_H