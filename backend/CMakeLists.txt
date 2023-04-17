cmake_minimum_required(VERSION 3.20)
project(sync)
find_library(LIB_CGICC cgicc)
find_library(LIB_SQLITE3 sqlite3)
find_library(LIB_PTHREAD pthread)

set(CMAKE_CXX_STANDARD 20)

add_executable(sync main.cpp database.cpp database.hpp md5.cpp md5.hpp files.cpp files.hpp download.cpp download.hpp notes.cpp notes.hpp)
target_link_libraries(sync ${LIB_CGICC})
target_link_libraries(sync ${LIB_SQLITE3})
target_link_libraries(sync ${LIB_PTHREAD})