target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mtrxstdafx.h
)

target_precompile_headers(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mtrxstdafx.h
)

add_subdirectory(INTERNAL)