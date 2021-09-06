target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_renderer_data.h
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_renderer_errors.h
)

add_subdirectory(Opengl)
add_subdirectory(Vulkan)