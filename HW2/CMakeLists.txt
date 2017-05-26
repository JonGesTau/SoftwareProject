cmake_minimum_required(VERSION 3.6)
project(HW2)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -c -fmessage-length=0 -std=c99 -Wall -Wextra -Werror -pedantic-errors")

set(SOURCE_FILES main.c)
add_executable(HW2 ${SOURCE_FILES})