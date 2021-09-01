#include "Matrix/Time/time.h"

#include "Matrix/Core/error.h"
#include "Matrix/Time/INTERNAL/INTERNAL_time.h"
#include "Matrix/Time/INTERNAL/INTERNAL_time_data.h"

int matrix_time_sec_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_sec;
	}
}

int matrix_time_min_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_min;
	}
}

int matrix_time_hour_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_hour;
	}
}

int matrix_time_mday_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_mday;
	}
}

int matrix_time_mon_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_mon;
	}
}

int matrix_time_year_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_year;
	}
}

int matrix_time_wday_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_wday;
	}
}

int matrix_time_yday_get(Matrix_Time* const time_)
{
	if (NULL == time_)
	{
		MTRX_ERROR_UNEXPECTED_NULL;
	}
	else
	{
		matrix_time_recent_make(time_);

		return time_->time_info.tm_yday;
	}
}