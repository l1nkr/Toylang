file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(logger STATIC ${srcs})

target_include_directories(logger PUBLIC include)
target_link_libraries(logger PUBLIC ast)