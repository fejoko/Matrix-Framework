target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/window.h
    ${CMAKE_CURRENT_LIST_DIR}/window_data.h
)

add_subdirectory(INTERNAL)