cmake_minimum_required(VERSION 3.0)


get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set (CMAKE_C_STANDARD 99)

file(GLOB SOURCES  *.c)

add_executable(${PROJECT_NAME} ${SOURCES} )