cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(nio CXX)

option(NIO_BUILD_TESTS "Build tests for nio" OFF)
option(NIO_BUILD_SHARED "Build a shared library too" OFF)

#==========================#

include_directories(include/)

file(GLOB_RECURSE NIO_SRC "src/*.cpp")

add_library(NioMain OBJECT ${NIO_SRC})
set_target_properties(NioMain PROPERTIES POSITION_INDEPENDENT_CODE 1)

add_library(NioStatic STATIC)
target_link_libraries(NioStatic NioMain)
set_target_properties(NioStatic PROPERTIES OUTPUT_NAME nio)

#==========================#

if(NIO_BUILD_SHARED)
	message(STATUS "nio: Building shared library")
	add_library(NioShared SHARED)
	target_link_libraries(NioShared NioMain)
	set_target_properties(NioShared PROPERTIES OUTPUT_NAME nio)
endif()

if(NIO_BUILD_TESTS)
	add_subdirectory(tests/)
endif()
