#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'test_accel_proc'
# 'make clean'  removes all .o and executable files
#

# Define shell utilites 
RM = rm -rf
MKDIR = mkdir -p

# Build directory
BUILD_DIR = ../../build/accel_scalar

# CIMLIB directory
CIMLIB_DIR = ../..

# Define the C compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
#
INCLUDES = \
	-I$(CIMLIB_DIR)/common/inc \
	-I../common

# Define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = \
	-L$(CIMLIB_DIR)/build/portable/release

# Define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = \
	-lcimlib

# Define the C source files
SRCS = \
	../common/csv.c \
	src/accel_proc.c \
	src/test_accel_proc.c

# Define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# Define the executable file 
MAIN = test_accel_proc

# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: build_cimlib \
	$(MAIN)
	@echo  Programm test_accel_proc has been compiled
	./$(BUILD_DIR)/$(MAIN)

$(MAIN): $(OBJS) 
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# This is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

build_cimlib:
	cd $(CIMLIB_DIR) && $(MAKE) portable release

clean:
	$(RM) $(BUILD_DIR)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it