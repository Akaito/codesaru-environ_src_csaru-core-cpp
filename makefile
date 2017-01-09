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

# Just for human convenience.
depend: .depend

# File with more Make build rules, built by the compiler's dependency crawling.
.depend: $(SRCS)
	$(CC) $(CXXFLAGS) -MM $? > .depend

clean:
	#-rm -rf $(TEMP_DIR)/*
	rm .depend

uninstall:
	-rm -rf $(CSaruDir)/pkg/$(PROJNAME)/*

(%.o): %.cpp
	echo $<
	echo $@
	@# $(CC) -c $(CXXFLAGS) $< -o $(TEMP_DIR)/$@

lib$(PROJNAME).a: $(OBJ)
	ar r $@ $?

include .depend

