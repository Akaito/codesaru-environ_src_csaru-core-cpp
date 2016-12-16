.PHONY: clean

# CSaruDir should be in your environment variables.
# It should have within it src, pkg, and bin directories.
include $(CSaruDir)/make-helpers.mk

HEADERS = include/csaru-core-cpp.h
SRC = src/LinuxOnly.cpp src/WindowsOnly.cpp
CC = clang $(CCFLAGS)

build: $(SRC) $(HEADERS)
	$(CC) $(SRC)

clean:
	-rm -rf $(CSaruDir)/pkg/csaru-core-cpp/*

