cmake_minimum_required(VERSION 3.1)
project(BigInt)

set(CMAKE_CXX_STANDARD 20)

add_executable(BigInt
		main.cpp
		SafeInt.cpp
		String.cpp
        safe_int_just_c.c
		DiS-p71and74.c
		twice_greater_v1.c
		)

include_directories(/home/courses/include ../HaverfordCS/include)
