#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_helpers.h"

#include "Matrix/Engine/engine_data.h"
#include "Matrix/Logger/logger_data.h"
#include "Matrix/Logger/INTERNAL/INTERNAL_logger.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager.h"
#include "Matrix/Statemanager/INTERNAL/INTERNAL_statemanager_data.h"
#include "Matrix/Vector/vector.h"

#include "stb/stb_sprintf.h"

void matrix_statemanager_log(const char* format, size_t state_index, Matrix_Statemanager* statemanager)
{
	if(statemanager->statemanager_settings.is_state_logging)
	{
		size_t len = strlen(MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, state_index, statemanager->states_vec_all).core.name);
		len += strlen(format); char* message = malloc(sizeof(*message) * len - 1);
		stbsp_sprintf(message, format, MTRX_VECTOR_AT_AS(Matrix_Statemanager_State, state_index, statemanager->states_vec_all).core.name);
		MTRX_CORE_LOG(message, MATRIX_LOGGER_LEVEL_TRACE, statemanager->data->logger);
		free(message);
	}
}