target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_window.h
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_window_data.h
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_window_errors.h
)

add_subdirectory(Glfw)