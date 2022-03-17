cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(nio CXX)

option(NIO_BUILD_TESTS "Build tests for nio" OFF)

#==========================#

if(NIO_BUILD_TESTS)
	add_subdirectory(tests/)
endif()
