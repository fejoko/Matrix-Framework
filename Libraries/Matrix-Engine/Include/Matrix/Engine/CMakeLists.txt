target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/engine.h
    ${CMAKE_CURRENT_LIST_DIR}/engine_data.h
)

add_subdirectory(INTERNAL)