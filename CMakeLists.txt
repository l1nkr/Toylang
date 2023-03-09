cmake_minimum_required(VERSION 3.13)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


project(main LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_subdirectory(ast)
add_subdirectory(kaleidoscope)
add_subdirectory(lexer)
add_subdirectory(logger)
add_subdirectory(parser)
add_subdirectory(main)
