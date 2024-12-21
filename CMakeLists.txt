cmake_minimum_required(VERSION 3.12)
project(CHRONOS CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/Common/include)

add_subdirectory(Agent)
add_subdirectory(Server)