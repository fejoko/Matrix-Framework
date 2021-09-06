target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_window.c
)

add_subdirectory(Glfw)