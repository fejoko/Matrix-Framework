#ifndef ___MTRX___TIME_H
#define ___MTRX___TIME_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Time Matrix_Time;

int matrix_time_sec_get(Matrix_Time* const time);
int matrix_time_min_get(Matrix_Time* const time);
int matrix_time_hour_get(Matrix_Time* const time);
int matrix_time_mday_get(Matrix_Time* const time);
int matrix_time_mon_get(Matrix_Time* const time);
int matrix_time_year_get(Matrix_Time* const time);
int matrix_time_wday_get(Matrix_Time* const time);
int matrix_time_yday_get(Matrix_Time* const time);

#endif // !___MTRX___TIME_H