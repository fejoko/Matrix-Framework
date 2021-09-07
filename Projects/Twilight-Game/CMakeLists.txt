cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Twilight-Game LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Twilight)

target_link_libraries(Twilight
    PUBLIC
    Matrix
)

target_compile_definitions(Twilight
       PUBLIC
       "___TWLT_DIR=\"${CMAKE_CURRENT_LIST_DIR}\""
)
target_compile_definitions(Twilight
       PUBLIC
       $<$<CONFIG:Debug>:
       
    >
)
target_compile_definitions(Twilight
       PUBLIC
       $<$<CONFIG:RelWithDebInfo>:
       
    >
)
target_compile_definitions(Twilight
       PUBLIC
       $<$<CONFIG:Release>:
       
    >
)
target_compile_definitions(Twilight
       PUBLIC
       $<$<CONFIG:MinSizeRel>:
       
    >
)

add_subdirectory(Include)
add_subdirectory(Source)