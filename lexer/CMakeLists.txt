file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
add_library(lexer STATIC ${srcs})

target_include_directories(lexer PUBLIC include)
target_link_libraries(lexer PUBLIC ${LLVM_LIBS})