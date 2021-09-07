#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"

#include "Matrix/Console/console.h"
#include "Matrix/Engine/INTERNAL/INTERNAL_engine_data.h"
#include "Matrix/Logger/logger.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger_errors.h"
#include "Matrix/Time/time.h"

#define STB_SPRINTF_IMPLEMENTATION
#include "Stb/stb_sprintf.h"

Matrix_Logger matrix_logger_construct()
{
	Matrix_Logger logger;
	logger.logger_settings = matrix_logger_settings_construct();
	logger.engine = NULL;
	logger.application = NULL;
	logger.time_ = NULL;

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

void matrix_logger_init(Matrix_Engine* const engine, Matrix_Application* const application, Matrix_Time* const time_, Matrix_Logger* const logger)
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
			logger->application = application;
			logger->time_ = time_;

			MTRX_CORE_PRELOG("logger: initialisation", MATRIX_LOGGER_LEVEL_INFO, logger->application);
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
		MTRX_CORE_PRELOG("logger: shutdown", MATRIX_LOGGER_LEVEL_INFO, logger->application);
	}
}

void matrix_logger_general_prelog(const char* message, const uint8_t flags, const Matrix_Logger_Level level, const Matrix_Application* const application)
{
	if (NULL == application)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (application->application_settings.is_prelogging)
		{
			const char* owner_color = "";
			const char* owner_name = "";
			const char* level_color = "";
			const char* level_name = "";

			if (MTRX_LOGGER_FLAG_CORE & flags)
			{
				owner_color = MATRIX_CONSOLE_COLOR_FG_GREEN;
				owner_name = "core";
			}
			else
			{
				owner_color = MATRIX_CONSOLE_COLOR_FG_BLUE;
				owner_name = "client";
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
				MTRX_ERROR_LOGGER_LEVEL_OUTOFBOUND;
				break;
			}

			MTRX_PRINTF("[%s%s%s][%s%s%s] %s\n", owner_color, owner_name, MATRIX_CONSOLE_COLOR_RESET, level_color, level_name, MATRIX_CONSOLE_COLOR_RESET, message);
		}
		else
		{
			//nothing
		}
	}
}

void matrix_logger_core_prelog(const char* message, const Matrix_Logger_Level level, const Matrix_Application* const application)
{
	matrix_logger_general_prelog(message, MTRX_LOGGER_FLAG_CORE, level, application);
}

void matrix_logger_general_log(const char* message, const Matrix_Logger_Level level, const uint8_t flags, const Matrix_Logger* const logger)
{
	if (NULL == logger)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (logger->logger_settings.is_logging)
		{
			if (level >= logger->logger_settings.minimal_level)
			{
				char* timestamp = "";
				const char* owner_color = "";
				const char* owner_name = "";
				const char* level_color = "";
				const char* level_name = "";

				if (logger->logger_settings.is_timestamp)
				{
					timestamp = NULL;
					timestamp = malloc(sizeof(*timestamp) * 11);
					if (NULL == timestamp)
					{
						MTRX_ERROR_MALLOC_FAILED;
					}
					else
					{
						if (NULL == logger->time_)
						{
							MTRX_ERROR_UNEXPECTED_NULL;
						}
						else
						{
							const char* s1 = "";
							const char* s2 = "";
							const char* s3 = "";

							if (9 >= matrix_time_hour_get(logger->time_))
							{
								s1 = "0";
							}
							else
							{
								//nothing
							}

							if (9 >= matrix_time_min_get(logger->time_))
							{
								s2 = "0";
							}
							else
							{
								//nothing
							}

							if (9 >= matrix_time_sec_get(logger->time_))
							{
								s3 = "0";
							}
							else
							{
								//nothing
							}

							stbsp_sprintf(timestamp, "[%s%i:%s%i:%s%i]", s1, matrix_time_hour_get(logger->time_), s2, matrix_time_min_get(logger->time_), s3, matrix_time_sec_get(logger->time_));
						}
					}
				}
				else
				{
					//nothing
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
						owner_name = logger->application->application_info.application_name;
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

				if (logger->logger_settings.is_timestamp)
				{
					free(timestamp);
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
			//nothing
		}
	}
}

void matrix_logger_core_log(const char* message, const Matrix_Logger_Level level, const Matrix_Logger* const logger)
{
	matrix_logger_general_log(message, level, MTRX_LOGGER_FLAG_CORE, logger);
}