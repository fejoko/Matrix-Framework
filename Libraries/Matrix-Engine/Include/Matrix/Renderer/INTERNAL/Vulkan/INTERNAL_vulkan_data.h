#ifndef ___MTRX___INTERNAL_VULKAN_DATA_H
#define ___MTRX___INTERNAL_VULKAN_DATA_H

#include "Matrix/Pch/INTERNAL/INTERNAL_mtrxstdafx.h"

#include "vulkan/vulkan.h"

typedef struct Matrix_Vulkan_Data
{
	uint32_t physical_device_used_index;
	VkFormat format_used;

	VkInstance instance;

	uint32_t physical_device_count;
	VkPhysicalDevice* physical_device_all;
	VkPhysicalDeviceProperties* physical_device_all_properties_all;
	VkPhysicalDeviceFeatures* physical_device_all_features_all;
	VkPhysicalDeviceMemoryProperties* physical_device_all_memory_properties_all;

	uint32_t queue_family_count;
	VkQueueFamilyProperties* queue_family_properties;
	VkBool32 surface_support_is;
	VkDevice device;
	VkQueue queue;

	VkSurfaceKHR surface;
	VkSurfaceCapabilitiesKHR surface_capabilities;
	uint32_t surface_format_count;
	VkSurfaceFormatKHR* surface_format_all;
	uint32_t present_mode_count;
	VkPresentModeKHR* present_mode_all;

	VkSwapchainKHR swapchain;
	uint32_t swapchain_image_count;
	VkImage* swapchain_image_all;

	VkImageView* image_view_all;

	VkShaderModule* shader_module_all;

	VkPipelineLayout pipeline_layout;
	VkRenderPass renderer_pass;
	VkPipeline pipeline;

	VkFramebuffer* frame_buffer_all;

	VkCommandPool command_pool;
	VkCommandBuffer* command_buffer_all;

	VkSemaphore semaphore_image_available;
	VkSemaphore semaphore_rendering_done;

} Matrix_Vulkan_Data;

#endif // !___MTRX___INTERNAL_VULKAN_DATA_H