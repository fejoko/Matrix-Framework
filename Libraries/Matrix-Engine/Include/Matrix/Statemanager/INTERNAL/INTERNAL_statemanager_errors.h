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
//----------------------------------

#endif // !___MTRX___INTERNAL_STATEMANAGER_ERRORS_H