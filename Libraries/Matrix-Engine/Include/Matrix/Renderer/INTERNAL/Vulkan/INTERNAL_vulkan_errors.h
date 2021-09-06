#ifndef ___MTRX___INTERNAL_VULKAN_ERRORS_H
#define ___MTRX___INTERNAL_VULKAN_ERRORS_H

#include "Matrix/Core/error.h"

//----------vulkan errors----------
#define MTRX_ERROR_VULKAN_VKRESULT_OUTOFBOUND \
MTRX_ERROR_EXIT("VkResult reached undefined value", "MTRX000x001x001r");
//----------------------------------

#endif // !___MTRX___INTERNAL_VULKAN_ERRORS_H