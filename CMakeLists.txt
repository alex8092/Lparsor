cmake_minimum_required(VERSION 2.8)

project(lparsor)

set(CMAKE_CXX_FLAGS "-std=c++11 -DLPARSOR_DEBUG -g3 -ggdb3 -O0")
SET(CMAKE_CXX_COMPILER g++)

include_directories(include/)

file(
	GLOB_RECURSE
	header_files
	include/*
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

add_executable(lparsor
	${header_files}
	${source_files})