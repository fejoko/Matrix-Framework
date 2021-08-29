#ifndef ___MTRX___LOGGER_DATA_H
#define ___MTRX___LOGGER_DATA_H

typedef struct Matrix_Logger Matrix_Logger;

typedef enum Matrix_Logger_Level
{
	MATRIX_LOGGER_LEVEL_DEBUG,
	MATRIX_LOGGER_LEVEL_TRACE,
	MATRIX_LOGGER_LEVEL_INFO,
	MATRIX_LOGGER_LEVEL_WARN,
	MATRIX_LOGGER_LEVEL_ERROR,
	MATRIX_LOGGER_LEVEL_CRITICAL,
} Matrix_Logger_Level;

typedef struct Matrix_Logger_Settings
{
	bool is_logging;
	bool is_timestamp;
	Matrix_Logger_Level minimal_level;
} Matrix_Logger_Settings;

#define MTRX_LOGGER_FLAG_A 0x02
#define MTRX_LOGGER_FLAG_B 0x04
#define MTRX_LOGGER_FLAG_C 0x08
#define MTRX_LOGGER_FLAG_D 0x16

#endif // !___MTRX___LOGGER_DATA_H