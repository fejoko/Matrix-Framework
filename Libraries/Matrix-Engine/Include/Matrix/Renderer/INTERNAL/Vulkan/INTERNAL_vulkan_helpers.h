#ifndef ___MTRX___INTERNAL_VULKAN_HELPERS_H
#define ___MTRX___INTERNAL_VULKAN_HELPERS_H

#include "vulkan/vulkan.h"

typedef struct Matrix_Renderer Matrix_Renderer;

void matrix_renderer_vulkan_assert(const char* what, VkResult result, bool no_success_info, Matrix_Renderer* const renderer);

#ifdef ___MTRX_NOLOG
#define MTRX_VULKAN_ASSERT(what, result, renderer)
#define MTRX_VULKAN_QASSERT(what, result, renderer)
#else
#define MTRX_VULKAN_ASSERT(what, result, renderer) \
matrix_renderer_vulkan_assert(what, result, false, renderer)
#define MTRX_VULKAN_QASSERT(what, result, renderer) \
matrix_renderer_vulkan_assert(what, result, true, renderer)
#endif // !___MTRX_NOLOG

#endif // !___MTRX___INTERNAL_VULKAN_HELPERS_H