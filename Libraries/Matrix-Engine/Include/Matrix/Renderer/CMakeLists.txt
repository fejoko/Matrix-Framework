target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/renderer.h
     ${CMAKE_CURRENT_LIST_DIR}/renderer_data.h
)

add_subdirectory(INTERNAL)