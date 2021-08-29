cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Matrix-Engine LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Matrix)

target_compile_definitions(Matrix
       PUBLIC
       
)
target_compile_definitions(Matrix
       PUBLIC
       $<$<CONFIG:Debug>:
       "___MTRX_DEBUG"
    >
)
target_compile_definitions(Matrix
       PUBLIC
       $<$<CONFIG:RelWithDebInfo>:
       "___MTRX_RELWITHDEBINFO"
    >
)
target_compile_definitions(Matrix
       PUBLIC
       $<$<CONFIG:Release>:
        "___MTRX_RELEASE"
    >
)
target_compile_definitions(Matrix
       PUBLIC
       $<$<CONFIG:MinSizeRel>:
       "___MTRX_MINSIZEREL"
    >
)

add_subdirectory(Include)
add_subdirectory(Libraries)
add_subdirectory(Source)