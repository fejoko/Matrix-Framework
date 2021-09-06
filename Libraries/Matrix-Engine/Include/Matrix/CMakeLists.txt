target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/matrix.h
)

add_subdirectory(Application)
add_subdirectory(Console)
add_subdirectory(Core)
add_subdirectory(Engine)
add_subdirectory(Logger)
add_subdirectory(Pch)
add_subdirectory(Renderer)
add_subdirectory(Statemanager)
add_subdirectory(Time)
add_subdirectory(Vector)
add_subdirectory(Window)