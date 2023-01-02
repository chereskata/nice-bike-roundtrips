cmake_minimum_required(VERSION 3.25)

project(nice-bike-roundtrips)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 99)

add_library(inih STATIC ${PROJECT_SOURCE_DIR}/include/inih/ini.c)
target_include_directories(inih PUBLIC ${PROJECT_SOURCE_DIR}/include/inih)

add_executable(nice-bike-roundtrips ${PROJECT_SOURCE_DIR}/src/main.c
			            ${PROJECT_SOURCE_DIR}/src/configuration.c)
#target_include_directories(nice-bike-roundtrips PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(nice-bike-roundtrips PRIVATE inih)
