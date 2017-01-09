# TODO
# 
# Read "A Super-Simple Makefile for Medium-Sized C/C++ Projects"
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
#
# Maybe also reference this:
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#

# Much of this Makefile was informed by:
# "A Super-Simple Makefile for Medium-Sized C/C++ Projects"
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

# CSaruDir should be in your environment variables.
# It should have within it src, pkg, and bin directories.
include $(CSaruDir)/make-helpers.mk

# =  -- Lazy set; recursively expanded when used, not when declared.
# := -- Immediate set; expand when declared.
# ?= -- Set variable only if absent.

PROJNAME = csaru-core-cpp
TARGET ?= a.out

HEADERS = include/csaru-core-cpp.h
OBJ = $(subst .cpp,.o,$(SRC))
TEMP_DIR = temp

SRC_DIRS ?= ./src

#SRCS = src/LinuxOnly.cpp src/WindowsOnly.cpp
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

# All directories in ./src, etc.
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# -MMD: -MD, without mentioning system header files.
# -MD: Write out Make-style dependencies for each file.
# -MP: Also write a phony rule for each header, so if a header is removed
#  without updating the file Make is using, it won't error.
CXXFLAGS := $(INC_FLAGS) -MMD -MP $(CXXFLAGS)


.PHONY: clean test

test:
	@echo $(CXXFLAGS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)

build: lib$(PROJNAME).a

# Just for human convenience.
depend: .depend
	@# Empty convenience rule.

# File with more Make build rules, built by the compiler's dependency crawling.
.depend: $(SRCS)
	$(CC) $(CXXFLAGS) -MM $? > .depend

clean:
	#-rm -rf $(TEMP_DIR)/*
	rm .depend

uninstall:
	-rm -rf $(CSaruDir)/pkg/$(PROJNAME)/*

# WIP. Believe this rule isn't being hit due to Make magic taking over.
(%.o): %.cpp
	echo $<
	echo $@
	# $(CC) -c $(CXXFLAGS) $< -o $(TEMP_DIR)/$@

lib$(PROJNAME).a: $(OBJ)
	ar r $@ $?

#include .depend

