#include "Matrix/Logger/logger.h"

#include "Matrix/Core/error.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_data.h"

Matrix_Logger_Settings matrix_logger_settings_construct()
{
	Matrix_Logger_Settings logger_settings;
	logger_settings.is_timestamp = false;

	return logger_settings;
}

void matrix_logger_settings_destruct(Matrix_Logger_Settings* const logger_settings)
{
	if (NULL == logger_settings)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_logger_settings_set(const Matrix_Logger_Settings logger_settings, Matrix_Logger* logger)
{
	if (NULL == logger)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		logger->logger_settings = logger_settings;
	}
}

void matrix_logger_client_log(const char* message, const Matrix_Logger_Level level, const Matrix_Logger* const logger)
{
	matrix_logger_general_log(message, level, MTRX_LOGGER_FLAG_CLIENT, logger);
}