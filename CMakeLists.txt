cmake_minimum_required(VERSION 3.1)
project(BigInt)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigInt
		main.cpp
		SafeInt.cpp
		String.cpp
		twice_greater_v1.c
		doubleInt.c
		BigInt.cpp BigInt.h)

include_directories(/home/courses/include ../HaverfordCS/include)
