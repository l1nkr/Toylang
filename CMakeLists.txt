cmake_minimum_required(VERSION 3.13)

project(main)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ast)
add_subdirectory(kaleidoscope)
add_subdirectory(lexer)
add_subdirectory(logger)
add_subdirectory(parser)

find_package(LLVM REQUIRED CONFIG)

add_compile_options(-I/usr/local/Cellar/llvm/13.0.1_1/include/ -std=c++14 -stdlib=libc++   -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
        -L/usr/local/Cellar/llvm/13.0.1_1/lib -Wl,-search_paths_first -Wl,-headerpad_max_install_names
        -lLLVM-13
)


#include_directories(/usr/local/Cellar/llvm/13.0.1_1/include/)


include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

#add_definitions(${LLVM_DEFINITIONS})


#add_compile_options(-I/usr/local/Cellar/llvm/13.0.1_1/include/llvm)
#add_compile_options(-I/usr/local/Cellar/llvm/13.0.1_1/include -fno-exceptions -fno-rtti -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

add_executable(main main.cpp)

#LINK_LIBRARIES(-L/usr/local/Cellar/llvm/13.0.1_1/lib -Wl,-search_paths_first -Wl,-headerpad_max_install_names)
#
#LINK_LIBRARIES(-lLLVM-13)

target_link_libraries(main PUBLIC ast)
target_link_libraries(main PUBLIC kaleidoscope)
target_link_libraries(main PUBLIC lexer)
target_link_libraries(main PUBLIC logger)
target_link_libraries(main PUBLIC parser)
#target_link_libraries(main PUBLIC /usr/local/Cellar/llvm/13.0.1_1/lib/)



