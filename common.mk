CXX := g++
CXXFLAGS := -Wall -std=c++17
CMD := $(CXX) $(CXXFLAGS)

# directories
OBJ := obj
SRC := src
BIN := bin
LIB := lib

# Capture the path to this file (common.mk)
THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

# Convert to an absolute path
COMMON_MK_PATH := $(abspath $(THIS_MAKEFILE))

# Extract the directory
ROOT := $(dir $(COMMON_MK_PATH))
