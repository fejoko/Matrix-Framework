cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(Matrix-Framework LANGUAGES C)

add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the debug mode."
)

add_custom_target(relwithdebinfo
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=RelWithDebInfo  ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the relwithdebinfo mode."
)

  add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the release mode."
)

add_custom_target(minsizerel
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=MinSizeRel  ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
    COMMENT "Creating the executable in the minsizerel mode."
)

add_subdirectory(Libraries)
add_subdirectory(Projects)