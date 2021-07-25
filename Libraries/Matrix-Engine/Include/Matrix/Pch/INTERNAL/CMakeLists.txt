target_sources(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_mtrxstdafx.h
    ${CMAKE_CURRENT_LIST_DIR}/PCH_stdarg.h
    ${CMAKE_CURRENT_LIST_DIR}/PCH_stdio.h
)

target_precompile_headers(Matrix
	PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/INTERNAL_mtrxstdafx.h
    ${CMAKE_CURRENT_LIST_DIR}/PCH_stdarg.h
    ${CMAKE_CURRENT_LIST_DIR}/PCH_stdio.h
)