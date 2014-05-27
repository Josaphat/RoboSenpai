project (RoboSenpai)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(gloox REQUIRED)

include_directories(${GLOOX_INCLUDE_DIR})

set(LIBS ${LIBS} ${GLOOX_LIBRARIES})

set(CMAKE_CXX_FLAGS "-W4 -std=c++11")

add_subdirectory(src)

