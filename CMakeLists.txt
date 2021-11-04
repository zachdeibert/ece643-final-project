cmake_minimum_required(VERSION 3.0)
project(ece643-final)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

add_subdirectory(downloader)
add_subdirectory(docker)
add_subdirectory(hwio-dbg)
add_subdirectory(libhwio)
