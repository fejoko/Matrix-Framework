#ifndef ___MTRX___INTERNAL_VULKAN_H
#define ___MTRX___INTERNAL_VULKAN_H

typedef struct Matrix_Renderer Matrix_Renderer;
typedef struct Matrix_Vulkan_Data Matrix_Vulkan_Data;

void matrix_vulkan_construct(Matrix_Renderer* const renderer);
void matrix_vulkan_init(Matrix_Renderer* const renderer);
void matrix_vulkan_start(Matrix_Renderer* const renderer);
void matrix_vulkan_update(Matrix_Renderer* const renderer);
void matrix_vulkan_stop(Matrix_Renderer* const renderer);
void matrix_vulkan_shutdown(Matrix_Renderer* const renderer);
void matrix_vulkan_destruct(Matrix_Renderer* const renderer);
void matrix_vulkan_onResize(Matrix_Renderer* const renderer);

void matrix_vulkan_swapchain_recreate(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

//init renderer
void matrix_vulkan_create_instance(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_enumerate_physical_devices(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_device(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

//start renderer
void matrix_vulkan_create_surface(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_shader(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_frame_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_command_pool(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_command_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_record_command_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_create_semaphore(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

//update renderer
void matrix_vulkan_frame_draw(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

//stop renderer
void matrix_vulkan_destroy_surface(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_swapchain(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_imageviews(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_shaders(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_pipeline(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_frame_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_command_pool(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_command_buffer(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_semaphore(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

//shutdown renderer
void matrix_vulkan_destroy_instance(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_denumerate_physical_devices(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);
void matrix_vulkan_destroy_device(Matrix_Vulkan_Data* api_data, Matrix_Renderer* renderer);

#endif // !___MTRX___INTERNAL_VULKAN_H