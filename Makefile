WARNING_FLAGS += -Wall -Wextra -Wpedantic
CFLAGS += $(WARNING_FLAGS)
CXXFLAGS += -g -std=c++11 $(WARNING_FLAGS)
CC := clang
CXX := clang++

# clang/gdb interop: http://lists.llvm.org/pipermail/llvm-bugs/2015-July/040993.html
CXXFLAGS += -D_GLIBCXX_DEBUG

.PHONY: clean

test: csaru-core.h test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test
	./test

clean:
	rm -f test
