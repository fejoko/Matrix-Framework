cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Matrix-Engine LANGUAGES C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Matrix)

target_link_libraries(Matrix
        PRIVATE
        glfw
)

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

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        message(STATUS "Configurating for Linux")
        target_compile_definitions(Matrix
            PUBLIC
            "___MTRX_LINUX"
        )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        message(STATUS "Configurating for Darwin")
        target_compile_definitions(Matrix
            PUBLIC
            "___MTRX_DARWIN"
        )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        message(STATUS "Configurating for Windows")
        target_compile_definitions(Matrix
            PUBLIC
            "___MTRX_WINDOWS"
        )
else()
       message(SEND_ERROR "Can not configurate on an unknown platform")
endif()

find_package(Vulkan)
if(Vulkan_FOUND)
	message(STATUS "VulkanSDK found")
    target_link_libraries(Matrix
        PRIVATE
        Vulkan::Vulkan
    )
    target_include_directories(Matrix
        PRIVATE
        ${VULKAN_INCLUDE_DIRS}
    )
	target_compile_definitions(Matrix
        PRIVATE
        "___MTRX_VULKAN"      
	)
else()
message(WARNING "VulkanSDK not found")
endif()

add_subdirectory(Include)
add_subdirectory(Libraries)
add_subdirectory(Source)