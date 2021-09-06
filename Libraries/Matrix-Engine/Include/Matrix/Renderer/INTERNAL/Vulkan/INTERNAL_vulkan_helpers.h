#ifndef ___MTRX___INTERNAL_VULKAN_HELPERS_H
#define ___MTRX___INTERNAL_VULKAN_HELPERS_H

#include "vulkan/vulkan.h"

typedef struct Matrix_Renderer Matrix_Renderer;

void matrix_vulkan_assert_result(const char* what, VkResult result, Matrix_Renderer* const renderer);

#endif // !___MTRX___INTERNAL_VULKAN_HELPERS_H