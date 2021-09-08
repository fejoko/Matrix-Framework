#ifndef ___MTRX___INTERNAL_VULKAN_HELPERS_H
#define ___MTRX___INTERNAL_VULKAN_HELPERS_H

#include "vulkan/vulkan.h"

typedef struct Matrix_Renderer Matrix_Renderer;

const char* matrix_renderer_result_match(VkResult result);

void matrix_renderer_vulkan_assert(const char* what, VkResult result, Matrix_Renderer* const renderer);
void matrix_renderer_vulkan_assert_index(const char* what, VkResult result, uint64_t index, Matrix_Renderer* const renderer);
void matrix_renderer_vulkan_assert_quiet(const char* what, VkResult result, Matrix_Renderer* const renderer);

#ifdef ___MTRX_NOLOG
#define MTRX_VULKAN_ASSERT(what, result, renderer)
#define MTRX_VULKAN_ASSERT_I(what, result, index, renderer)
#define MTRX_VULKAN_ASSERT_Q(what, result, renderer)
#else
#define MTRX_VULKAN_ASSERT(what, result, renderer) \
matrix_renderer_vulkan_assert(what, result, renderer)
#define MTRX_VULKAN_ASSERT_I(what, result, index, renderer) \
matrix_renderer_vulkan_assert_index(what, result, index, renderer)
#define MTRX_VULKAN_ASSERT_Q(what, result, renderer) \
matrix_renderer_vulkan_assert_quiet(what, result, renderer)
#endif // !___MTRX_NOLOG

#endif // !___MTRX___INTERNAL_VULKAN_HELPERS_H