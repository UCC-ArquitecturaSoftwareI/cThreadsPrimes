cmake_minimum_required(VERSION 3.14)
project(primos)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(primos main.cpp safeQueue.cpp)