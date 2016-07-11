cmake_minimum_required(VERSION 2.6)
project(lpl)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_subdirectory("./liblpl")

add_executable(lpl ${CMAKE_SOURCE_DIR}/src/lpl.c)
target_link_libraries(lpl ${CMAKE_SOURCE_DIR}/liblpl.a)

