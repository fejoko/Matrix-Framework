#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"

#include "Matrix/Console/console.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/logger.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_errors.h"

Matrix_Logger matrix_logger_construct()
{
	Matrix_Logger logger;
	logger.is_initialised = false;
	logger.logger_settings = matrix_logger_settings_construct();
	logger.engine = NULL;

	return logger;
}

void matrix_logger_destruct(Matrix_Logger* const logger)
{
	if (NULL == logger)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_logger_settings_destruct(&logger->logger_settings);
	}
}

void matrix_logger_init(Matrix_Engine* const engine, Matrix_Logger* const logger)
{
	if (NULL == engine)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (NULL == logger)
		{
			MTRX_ERROR_UNEXPECTED_NULL;
		}
		else
		{
			logger->engine = engine;
			logger->is_initialised = true;
		}
	}
}

void matrix_logger_shutdown(Matrix_Logger* const logger)
{
	if (NULL == logger)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		logger->is_initialised = false;
	}
}

void matrix_general_log(const char* message, const Matrix_Logger_Level level, const uint8_t flags, const Matrix_Logger* const logger)
{
	if (NULL == logger)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (logger->is_initialised)
		{
			if (logger->logger_settings.is_logging)
			{
				if (level >= logger->logger_settings.minimal_level)
				{
					const char* timestamp = "";
					const char* owner_color = "";
					const char* owner_name = "";
					const char* level_color = "";
					const char* level_name = "";

					if (logger->logger_settings.is_timestamp)
					{
						timestamp = "[xx:xx:xx]";
					}
					else
					{
						timestamp = "";
					}

					if (NULL == logger->engine)
					{
						MTRX_ERROR_UNEXPECTED_NULL;
					}
					else
					{
						if (MTRX_LOGGER_FLAG_CORE & flags)
						{
							owner_color = MATRIX_CONSOLE_COLOR_FG_GREEN;
							owner_name = logger->engine->engine_info.ENGINE_NAME;
						}
						else
						{
							owner_color = MATRIX_CONSOLE_COLOR_FG_BLUE;
							owner_name = logger->engine->application.application_info.application_name;
						}
					}

					switch (level)
					{
					case MATRIX_LOGGER_LEVEL_DEBUG:
						level_color = "";
						level_name = "debug";
						break;
					case MATRIX_LOGGER_LEVEL_TRACE:
						level_color = MATRIX_CONSOLE_COLOR_FG_PURPLE;
						level_name = "trace";
						break;
					case MATRIX_LOGGER_LEVEL_INFO:
						level_color = MATRIX_CONSOLE_COLOR_FG_CYAN;
						level_name = "info";
						break;
					case MATRIX_LOGGER_LEVEL_WARN:
						level_color = MATRIX_CONSOLE_COLOR_FG_YELLOW;
						level_name = "warn";
						break;
					case MATRIX_LOGGER_LEVEL_ERROR:
						level_color = MATRIX_CONSOLE_COLOR_FG_RED;
						level_name = "error";
						break;
					case MATRIX_LOGGER_LEVEL_CRITICAL:
						level_color = MATRIX_CONSOLE_COLOR_BG_RED;
						level_name = "critical";
						break;
					default:
						break;
					}

					MTRX_PRINTF("%s[%s%s%s][%s%s%s] %s\n", timestamp, owner_color, owner_name, MATRIX_CONSOLE_COLOR_RESET, level_color, level_name, MATRIX_CONSOLE_COLOR_RESET, message);
				}
				else
				{
					//nothing
				}
			}
			else
			{
				//nothing
			}
		}
		else
		{
			MTRX_ERROR_LOGGER_UNINITIALISED;
		}
	}
}

void matrix_logger_core_log(const char* message, const Matrix_Logger_Level level, const Matrix_Logger* const logger)
{
	matrix_general_log(message, level, MTRX_LOGGER_FLAG_CORE, logger);
}