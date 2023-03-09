file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
add_library(logger STATIC ${srcs})

target_include_directories(logger PUBLIC include)
target_link_libraries(logger PUBLIC ast)
target_link_libraries(logger PUBLIC ${LLVM_LIBS})