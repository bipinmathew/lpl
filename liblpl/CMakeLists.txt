cmake_minimum_required(VERSION 2.6)
project(liblpl)
include(ExternalProject)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")


add_library(${PROJECT_NAME} STATIC src/parser.c src/lpl_scanner.c src/lpl_parser.c src/node.c src/arithmetic.c src/logical.c )
target_link_libraries(liblpl LINK_PUBLIC libcol)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

add_subdirectory("./libs/libcol")

ExternalProject_Add(c-algorithms
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/c-algorithms
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libs/c-algorithms/configure --prefix=<INSTALL_DIR>
    BUILD_COMMAND ${MAKE})


find_program(AWK NAMES gawk nawk awk)
find_program(LEMON NAMES lemon)
find_program(LEX NAMES flex lex)



message("Found AWK: ${AWK}")

## Build logical and arithmetic source files.

add_custom_command(
  OUTPUT  src/arithmetic.c
	COMMAND ${AWK} -f compile_arithmetic.awk < dyadic.tpl > arithmetic.c  
	COMMAND ./compile_arithmetic.sh arithmetic.tpl > arithmetic.inl 
  WORKING_DIRECTORY ./src
  DEPENDS src/arithmetic.inl
  COMMENT "Generating arithmetic.c"
)

add_custom_command(
  OUTPUT src/arithmetic.inl
	COMMAND ./compile_arithmetic.sh arithmetic.tpl > arithmetic.inl 
  WORKING_DIRECTORY ./src
  COMMENT "Generating arithmetic.inl"
)


add_custom_command(
  OUTPUT src/logical.inl src/logical.c
	COMMAND ${AWK} -f compile_logical.awk < dyadic.tpl > logical.c  
	COMMAND ./compile_logical.sh logical.tpl > logical.inl 
  WORKING_DIRECTORY ./src
  COMMENT "Generating logical.c"
)


## Build lexer and parser source files.

add_custom_command(
  OUTPUT lpl_scanner.h lpl_scanner.c 
	COMMAND ${LEX} --reentrant --header-file=lpl_scanner.h --outfile=lpl_scanner.c lpl_scanner.l 
  WORKING_DIRECTORY ./src
  COMMENT "Generating lexer"
)

add_custom_command(
  OUTPUT lpl_parser.c lpl_parser.h 
	COMMAND ${LEMON}  -s -p lpl_parser.y
  WORKING_DIRECTORY ./src
  DEPENDS lpl_scanner.h
  COMMENT "Generating parser"
)

## Compile into a library.

set(${PROJECT_NAME}_sources ${PROJECT_SOURCE_DIR}/src/libcol.c )


include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/libs/libcol/include
  ${PROJECT_SOURCE_DIR}/libs/c-algorithms/src
)



install ( TARGETS ${PROJECT_NAME}
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib/static)

