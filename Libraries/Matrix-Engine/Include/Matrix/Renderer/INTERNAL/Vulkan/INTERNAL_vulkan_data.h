#ifndef ___MTRX___INTERNAL_VULKAN_DATA_H
#define ___MTRX___INTERNAL_VULKAN_DATA_H

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"

#include "vulkan/vulkan.h"

typedef struct Matrix_Vulkan_Data
{
	VkInstance instance;

	uint32_t physical_device_amount;
	VkPhysicalDevice* physical_device_all;
	VkPhysicalDeviceProperties* physical_device_all_properties;
	VkPhysicalDeviceFeatures* physical_device_all_features;
	VkPhysicalDeviceMemoryProperties* physical_device_all_memory_properties;
	uint32_t physical_device_used_index;

	uint32_t queue_family_count;
	VkQueueFamilyProperties* queue_family_properties;
	VkSurfaceKHR surface;
	VkDevice device;
	VkQueue queue;
} Matrix_Vulkan_Data;

#endif // !___MTRX___INTERNAL_VULKAN_DATA_H