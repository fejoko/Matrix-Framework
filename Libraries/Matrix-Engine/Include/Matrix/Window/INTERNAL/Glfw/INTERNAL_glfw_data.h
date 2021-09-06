#ifndef ___MTRX___INTERNAL_GLDW_DATA_H
#define ___MTRX___INTERNAL_GLDW_DATA_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

typedef struct Matrix_Glfw_Data
{
	GLFWwindow* glfw_window;
} Matrix_Glfw_Data;

#endif // !___MTRX___INTERNAL_GLDW_DATA_H