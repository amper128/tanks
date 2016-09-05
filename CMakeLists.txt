cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(tanks)

find_library(pugixml REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "-Os -Wall -pipe")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "-O0 -ggdb")
set(CMAKE_CXX_FLAGS "-Os -Wall -pipe")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb")

add_subdirectory(src)
