project (RoboSenpai)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(gloox REQUIRED)

include_directories(${gloox_INCLUDE_DIR})

set(LIBS ${LIBS} ${gloox_LIBRARIES})

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_subdirectory(RoboSenpai)

