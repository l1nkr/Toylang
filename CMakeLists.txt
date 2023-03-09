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

add_executable(main main.cpp)

find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
# include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(main PUBLIC ast)
target_link_libraries(main PUBLIC kaleidoscope)
target_link_libraries(main PUBLIC lexer)
target_link_libraries(main PUBLIC logger)
target_link_libraries(main PUBLIC parser)
target_link_libraries(main PUBLIC ${LLVM_LIBS})

# target_include_directories(main PRIVATE ${LLVM_INCLUDE_DIRS})
# target_link_libraries(main PRIVATE ${LLVM_LIBS})
target_compile_definitions(main PRIVATE ${LLVM_DEFINITIONS})
