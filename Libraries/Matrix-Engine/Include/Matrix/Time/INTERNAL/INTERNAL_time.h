#ifndef ___MTRX___INTERNAL_TIME_H
#define ___MTRX___INTERNAL_TIME_H

typedef struct Matrix_Time Matrix_Time;

Matrix_Time matrix_time_construct();
void matrix_time_destruct(Matrix_Time* const time);

void matrix_time_update(Matrix_Time* const time);

void matrix_time_recent_make(Matrix_Time* const time);

#endif // !___MTRX___INTERNAL_TIME_H