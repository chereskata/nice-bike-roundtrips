cmake_minimum_required(VERSION 3.25)

project(nice-bike-roundtrips)

set(CMAKE_BUILD_TYPE Debug)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(app ${PROJECT_SOURCE_DIR}/src/main.c)
