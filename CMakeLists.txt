cmake_minimum_required(VERSION 3.0)
project(GameBox)

set(CMAKE_CXX_FLAGS "-std=c++11")

aux_source_directory(./src SRC)

include_directories(./src)

add_executable(gamebox ${SRC})