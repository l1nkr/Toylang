
find_package(LLVM REQUIRED CONFIG)

include_directories(${PROJECT_SOURCE_DIR})

include_directories(${LLVM_INCLUDE_DIRS})
#include_directories(/usr/local/Cellar/llvm/13.0.1_1/include/llvm)
#include_directories(/usr/local/Cellar/llvm/13.0.1_1/include/llvm)
#add_compile_options(-I/usr/local/Cellar/llvm/13.0.1_1/include/)
#add_compile_options(-I/usr/local/Cellar/llvm/13.0.1_1/include/ -std=c++14 -stdlib=libc++   -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
#        -L/usr/local/Cellar/llvm/13.0.1_1/lib -Wl,-search_paths_first -Wl,-headerpad_max_install_names
#        -lLLVM-13
#        )
#include_directories(${LLVM_INCLUDE_DIRS})

#find_package(LLVM REQUIRED CONFIG)
#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})

#find_package(LLVM REQUIRED CONFIG)



add_library(CallExprAST STATIC CallExprAST.cpp)
add_library(FunctionAST STATIC FunctionAST.cpp)
add_library(NumberExprAST STATIC NumberExprAST.cpp)
add_library(PrototypeAST STATIC PrototypeAST.cpp)
add_library(VariableExprAST STATIC VariableExprAST.cpp)
add_library(BinaryExprAST STATIC BinaryExprAST.cpp)
#target_include_directories(BinaryExprAST PUBLIC ${LLVM_INCLUDE_DIRS})

