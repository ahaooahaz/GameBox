CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(GameBox)

SET(CMAKE_CXX_FLAGS "-std=c++11")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src SRC)

ADD_EXECUTABLE(gamebox ${SRC})