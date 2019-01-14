cmake_minimum_required(VERSION 3.13)
project(cpp-t9)

#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -mtune=native -std=c++17")

# CMAKE_CXX_FLAGS_DEBUG contains "-g" by default.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# CMAKE_CXX_FLAGS_RELEASE contains "-O3 -DNDEBUG" by default.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lstdc++fs")

#set( CMAKE_VERBOSE_MAKEFILE on )

#include_directories(SYSTEM libs)
include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/format.cpp
        src/t9/timer.cpp
        src/t9/math.cpp
        src/t9/io.cpp
        src/t9/corpus.cpp
        src/t9/generator.cpp
        src/t9/node.cpp
        src/t9/path.cpp
        src/t9/tree.cpp
        src/t9/model.cpp)

add_definitions("-lmath")

add_executable(cpp-t9 ${SOURCE_FILES})

#add_subdirectory(libs/googletest)
#include_directories(libs/googletest/googletest/include libs/googletest/googletest)

#set(SOURCE_FILES_TESTS
#        tests/test-sandbox.cpp)

#add_executable(cpp-t9-tests ${SOURCE_FILES} ${SOURCE_FILES_TESTS})
#target_link_libraries(cpp-t9-tests gtest gtest_main)
