cmake_minimum_required(VERSION 3.20)
project(sync)
find_library(LIB_CGICC cgicc)
find_library(LIB_SQLITE3 sqlite3)
find_library(LIB_PTHREAD pthread)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
add_subdirectory(socket)

add_executable(sync main.cpp database.cpp database.hpp md5.cpp md5.hpp files.cpp files.hpp download.cpp download.hpp notes.cpp notes.hpp)

target_link_libraries(sync socket_lib)
target_link_libraries(sync ${LIB_CGICC})
target_link_libraries(sync ${LIB_SQLITE3})
target_link_libraries(sync ${LIB_PTHREAD})
