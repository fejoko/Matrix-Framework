target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_renderer.c
)

add_subdirectory(Opengl)
add_subdirectory(Vulkan)