target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/logger.h
    ${CMAKE_CURRENT_LIST_DIR}/logger_data.h
)

add_subdirectory(INTERNAL)