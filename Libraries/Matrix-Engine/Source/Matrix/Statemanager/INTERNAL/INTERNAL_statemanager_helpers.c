#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_helpers.h"

#include "Matrix/Core/error.h"
#include "Matrix/Engine/engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Vector/vector.h"

#include "Stb/stb_sprintf.h"

void matrix_statemanager_log(const char* format, size_t state_index, Matrix_Statemanager* statemanager)
{
	size_t len = strlen(MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, state_index, statemanager->states_vec_all).core.name);
	len += strlen(format);
	char* message = NULL;
	message = malloc(sizeof(*message) * len - 1);
	if (NULL == message)
	{
		MTRX_ERROR_MALLOC_FAILED;
	}
	else
	{
		stbsp_sprintf(message, format, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, state_index, statemanager->states_vec_all).core.name);
		MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_TRACE, statemanager->logger);
		free(message);
	}
}