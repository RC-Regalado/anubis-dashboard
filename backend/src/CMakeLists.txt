cmake_minimum_required(VERSION 3.20)
project(sync)
find_library(LIB_SQLITE3 sqlite3)
find_library(LIB_PTHREAD pthread)
find_library(LIB_JSONCPP jsoncpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(sync 
  main.cpp 
  
  socket/exceptions.cpp 
  socket/exceptions.hpp 
  socket/socket.cpp 
  socket/socket.hpp 
  socket/pool.cpp 
  socket/pool.hpp 
  socket/client.cpp 
  socket/client.hpp 

  tools/utils.cpp
  tools/utils.hpp
  tools/md5.cpp 
  tools/md5.hpp 

  methods/method.cpp
  methods/method.hpp
  methods/delete.cpp
  methods/delete.hpp
  methods/get.cpp
  methods/get.hpp
  methods/post.cpp
  methods/post.hpp
  methods/patch.cpp
  methods/patch.hpp
)

target_link_libraries(sync ${LIB_SQLITE3})
target_link_libraries(sync ${LIB_PTHREAD})
target_link_libraries(sync ${LIB_JSONCPP})
