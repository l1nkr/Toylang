SOURCES = $(shell find ast kaleidoscope lexer logger parser -name '*.cpp')
HEADERS = $(shell find ast kaleidoscope lexer logger parser -name '*.h')
OBJ = ${SOURCES:.cpp=.o}

CC = llvm-g++ -stdlib=libc++ -std=c++14
CFLAGS = -g -W -I llvm/include -I llvm/build/include -I ./
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs all`
#debug: CFLAGS += -g -O0 -Wall -Wextra

.PHONY: main

debug: main

main: main.cpp ${OBJ}
	${CC} ${CFLAGS} ${LLVMFLAGS} ${OBJ} $< -o $@

clean:
	rm -r ${OBJ}

%.o: %.cpp ${HEADERS}
	${CC} ${CFLAGS} ${LLVMFLAGS} -c $< -o $@
