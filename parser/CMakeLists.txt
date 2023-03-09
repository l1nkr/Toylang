file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_library(parser STATIC ${srcs})
target_include_directories(parser PUBLIC include)

target_link_libraries(parser PUBLIC ast)
target_link_libraries(parser PUBLIC lexer)