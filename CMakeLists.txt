cmake_minimum_required(VERSION 2.6)
project(lpl)
add_definitions(-DDEBUG)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_subdirectory("./liblpl")

include_directories(
  ${CMAKE_SOURCE_DIR}/liblpl/c-algorithms-prefix/include/libcalg-1.0/libcalg
  ${CMAKE_SOURCE_DIR}/liblpl/include
  ${CMAKE_SOURCE_DIR}/liblpl/libs/libcol/include
  ${CMAKE_SOURCE_DIR}/liblpl/src
)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/lpl.c)
set(HEADERS 
  ${CMAKE_SOURCE_DIR}/liblpl/c-algorithms-prefix/include/libcalg-1.0/libcalg/trie.h
  ${CMAKE_SOURCE_DIR}/liblpl/libs/libcol/include/col.h
)


add_executable(lpl ${SOURCES} ${HEADERS})
target_link_libraries(lpl 
  LINK_PUBLIC liblpl
  LINK_PUBLIC ${CMAKE_SOURCE_DIR}/liblpl/c-algorithms-prefix/lib/libcalg.a  
)

