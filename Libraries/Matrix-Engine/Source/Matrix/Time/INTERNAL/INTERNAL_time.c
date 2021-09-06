#include "Matrix/Time/INTERNAL/INTERNAL_time.h"

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"
#include "Matrix/Core/error.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Time/INTERNAL/INTERNAL_time_data.h"

Matrix_Time matrix_time_construct()
{
	Matrix_Time time_;
	time_.is_recent = false;
	time_.time_raw = 0;
	time_.time_info;
	time_.application = NULL;

	return time_;
}

void matrix_time_destruct(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
	}
}

void matrix_time_init(Matrix_Application* const application, Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		time_->application = application;

		MTRX_CORE_PRELOG("time: initialisation", MATRIX_LOGGER_LEVEL_INFO, application);
	}
}

void matrix_time_update(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		time_->is_recent = false;
	}
}

void matrix_time_shutdown(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		MTRX_CORE_PRELOG("time: shutdown", MATRIX_LOGGER_LEVEL_INFO, time_->application);
	}
}

void matrix_time_recent_make(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		if (time_->is_recent)
		{
			//nothing
		}
		else
		{
			time_->time_raw = time(NULL);
			localtime_s(&time_->time_info, &time_->time_raw);
		}
	}
}