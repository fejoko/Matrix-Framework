target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/statemanager.h
     ${CMAKE_CURRENT_LIST_DIR}/statemanager_data.h
)

add_subdirectory(INTERNAL)