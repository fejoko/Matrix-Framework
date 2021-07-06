target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/matrix.h
)

add_subdirectory(Console)
add_subdirectory(Core)
add_subdirectory(Pch)
add_subdirectory(Statemanager)
add_subdirectory(Vector)