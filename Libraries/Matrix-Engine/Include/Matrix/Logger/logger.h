#ifndef ___MTRX___LOGGER_H
#define ___MTRX___LOGGER_H

#include "Matrix/Pch/mtrxstdafx.h"

typedef struct Matrix_Logger Matrix_Logger;
typedef struct Matrix_Logger_Settings Matrix_Logger_Settings;
typedef enum Matrix_Logger_Level Matrix_Logger_Level;

Matrix_Logger_Settings matrix_logger_settings_construct();
void matrix_logger_settings_destruct(Matrix_Logger_Settings* const logger_settings);

void matrix_logger_settings_set(Matrix_Logger_Settings logger_settings, Matrix_Logger* logger);

void matrix_logger_client_log(const char* message, const Matrix_Logger_Level level, const Matrix_Logger* const logger);

#ifdef ___MTRX_NOLOG
#define MTRX_LOG(message, level, logger)
#else
#define MTRX_LOG(message, level, logger) \
matrix_logger_client_log(message, level, logger)
#endif // !___MTRX_NOLOG

#endif // !___MTRX___LOGGER_H