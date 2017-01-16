#===============================================================================
# Common parameters make file
#===============================================================================

# Utilites 
RM = rm -rf
MKDIR = mkdir -p
PYTHON = python 

# Build directory
BUILD_DIR = ../../build

# Library name 
TARGET = cimlib
TARGET_LIB = libcimlib.a
TARGET_DEBUG = $(TARGET_LIB)
TARGET_RELEASE = $(TARGET_LIB)

# All project source and header files
SOURCES_ALL = $(shell find . -type f -iname '*.[c,h]')
