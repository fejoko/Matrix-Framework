target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/application.h
    ${CMAKE_CURRENT_LIST_DIR}/application_data.h
)

add_subdirectory(INTERNAL)