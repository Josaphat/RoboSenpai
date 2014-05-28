project (RoboSenpai)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(gloox REQUIRED)
find_package(YamlCpp REQUIRED)

include_directories(${GLOOX_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR})

set(LIBS ${LIBS} ${GLOOX_LIBRARIES} ${YAMLCPP_LIBRARY})

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.yml ${CMAKE_CURRENT_BINARY_DIR}/config.yml COPYONLY)

add_subdirectory(src)
