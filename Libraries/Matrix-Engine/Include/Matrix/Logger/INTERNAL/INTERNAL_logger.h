#ifndef ___MTRX___INTERNAL_LOGGER_H
#define ___MTRX___INTERNAL_LOGGER_H

typedef struct Matrix_Engine Matrix_Engine;
typedef struct Matrix_Time Matrix_Time;
typedef struct Matrix_Logger Matrix_Logger;
typedef enum Matrix_Logger_Level Matrix_Logger_Level;

Matrix_Logger matrix_logger_construct();
void matrix_logger_destruct(Matrix_Logger* const logger);

void matrix_logger_init(Matrix_Engine* const engine, Matrix_Time* const time, Matrix_Logger* const logger);
void matrix_logger_shutdown(Matrix_Logger* const logger);

void matrix_logger_general_prelog(const char* message, const uint8_t flags, const Matrix_Logger_Level level);
void matrix_logger_core_prelog(const char* message, const Matrix_Logger_Level level);

void matrix_logger_general_log(const char* message, const Matrix_Logger_Level level, const uint8_t flags, const Matrix_Logger* const logger);
void matrix_logger_core_log(const char* message, const Matrix_Logger_Level level, const Matrix_Logger* const logger);

#ifdef ___MTRX_NOLOG
#define MTRX_CORE_PRELOG(message, level)
#define MTRX_CORE_LOG(message, level, logger)
#else
#define MTRX_CORE_PRELOG(message, level) \
matrix_logger_core_prelog(message, level)
#define MTRX_CORE_LOG(message, level, logger) \
matrix_logger_core_log(message, level, logger)
#endif // !___MTRX_NOLOG

#endif // !___MTRX___INTERNAL_LOGGER_H