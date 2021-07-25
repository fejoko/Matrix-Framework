#ifndef ___MTRX___INTERNAL_STATEMANAGER_ERRORS_H
#define ___MTRX___INTERNAL_STATEMANAGER_ERRORS_H

#include "Matrix/Core/error.h"

//----------statemanager errors----------
#define MTRX_ERROR_STATEMANAGER_INVALID_STATE_NAME \
MTRX_ERROR_EXIT("invalid state_name", "MTRX000x001x000s");

#define MTRX_ERROR_STATEMANAGER_NOTUNIQUE_STATE_NAME \
MTRX_ERROR_EXIT("notunique state_name", "MTRX000x002x000s");

#define MTRX_ERROR_STATEMANAGER_MISSING_DEFAULT \
MTRX_ERROR_EXIT("default state was missing", "MTRX000x003x000s");

#define MTRX_ERROR_STATEMANAGER_STATE_LOAD_ALREADY \
MTRX_ERROR_EXIT("state was already loaded", "MTRX000x004x001s");

#define MTRX_ERROR_STATEMANAGER_STATE_LOAD_NOT \
MTRX_ERROR_EXIT("state was not loaded", "MTRX000x004x002s");
//----------------------------------

#endif // !___MTRX___INTERNAL_STATEMANAGER_ERRORS_H