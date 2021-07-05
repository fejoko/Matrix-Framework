#ifndef ___MTRX___CONFIGURATION_H
#define ___MTRX___CONFIGURATION_H

#include "Matrix/Pch/mtrxstdafx.h"

#ifdef ___MTRX_DEBUG
#define MTRX_DEBUG_IS true
#else
#define MTRX_DEBUG_IS false
#endif

#ifdef ___MTRX_RELWITHDEBINFO
#define MTRX_RELWITHDEBINFO_IS true
#else
#define MTRX_RELWITHDEBINFO_IS false
#endif

#ifdef ___MTRX_RELEASE
#define MTRX_RELEASE_IS true
#else
#define MTRX_RELEASE_IS false
#endif

#ifdef ___MTRX_MINSIZEREL
#define MTRX_MINSIZEREL_IS true
#else
#define MTRX_MINSIZEREL_IS false
#endif

#endif // !___MTRX___CONFIGURATION_H