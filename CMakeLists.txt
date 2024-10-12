# Minimum version of CMake
cmake_minimum_required(VERSION 3.14)

# Project name and languages
project(SQLITE-CPP)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure destination output executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define the source files
# Include all source files from different directories
set(SOURCES
    src/main.cpp
    src/lib/argparser/argparser.cpp
    src/lib/utils/strings.cpp
    src/lib/utils/numbers.cpp
    src/lib/utils/bits.cpp
    src/lib/utils/math.cpp
    src/lib/utils/varint.cpp
    src/lib/dot-commands/dot-commands.cpp
    src/lib/dot-commands/dbinfo.cpp
    src/lib/dot-commands/tables.cpp
)

# Define the include directories (where the header files are)
include_directories(
    src/lib/argparser
    src/lib/utils
)

# Create the main executable
add_executable(sqlite-cpp ${SOURCES})

# Additional options or flags (if necessary)
# target_compile_options(MyCppProject PRIVATE -Wall -Wextra)


# GOOGLE TEST SETUP

# include FetchContent plugin
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(
  tests
  src/lib/argparser/argparser.cpp
  src/lib/argparser/argparser.tests.cpp
  src/lib/utils/strings.cpp
  src/lib/utils/numbers.cpp
  src/lib/utils/bits.cpp
  src/lib/utils/math.cpp
  src/lib/utils/varint.cpp
  src/lib/utils/varint.tests.cpp
)

target_include_directories(
  tests PRIVATE
  src/lib/argparser
)

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
