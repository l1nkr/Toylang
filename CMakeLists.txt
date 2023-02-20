cmake_minimum_required(VERSION 3.10)

project(toylang)

include_directories(./src ./tests)
# include_directories(./tests)
# configure_file(./src/lexical.h)
add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

add_executable(test_lex lexical.c++)