.PHONY: clean

# CSaruDir should be in your environment variables.
# It should have within it src, pkg, and bin directories.
include $(CSaruDir)/make-helpers.mk

PROJNAME = csaru-core-cpp
HEADERS = include/csaru-core-cpp.h
SRCS = src/LinuxOnly.cpp src/WindowsOnly.cpp
OBJ = $(subst .cpp,.o,$(SRC))
TEMP_DIR = temp

build: lib$(PROJNAME).a

depend: .depend

.depend: $(SRCS)
	$(CC) $(CPPFLAGS) -MM $? > .depend

clean:
	#-rm -rf $(TEMP_DIR)/*
	rm .depend

uninstall:
	-rm -rf $(CSaruDir)/pkg/$(PROJNAME)/*

(%.o): %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $(TEMP_DIR)/$@

lib$(PROJNAME).a: $(OBJ)
	ar r $@ $?

include .depend

