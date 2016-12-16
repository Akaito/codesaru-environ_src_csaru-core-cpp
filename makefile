.PHONY: clean

# CSaruDir should be in your environment variables.
# It should have within it src, pkg, and bin directories.
include $(CSaruDir)/make-helpers.mk

PROJNAME = csaru-core-cpp
HEADERS = include/csaru-core-cpp.h
SRC = src/LinuxOnly.cpp src/WindowsOnly.cpp
TEMP_DIR = temp/

build: $(SRC) $(HEADERS)
	#-mkdir $(TEMP_DIR)
	$(CC) -c $(SRC)
	ar rcs lib$(PROJNAME).a *.o

clean:
	-rm -rf $(TEMP_DIR)/*

uninstall:
	-rm -rf $(CSaruDir)/pkg/$(PROJNAME)/*

