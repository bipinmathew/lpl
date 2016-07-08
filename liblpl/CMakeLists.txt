cmake_minimum_required(VERSION 2.6)
project(liblpl)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")


add_subdirectory("../libcol")


find_program(AWK NAMES gawk nawk awk)
find_program(LEMON NAMES lemon)
find_program(LEX NAMES flex lex)

message("Found AWK: ${AWK}")

add_custom_command(
  OUTPUT arithmetic.c arithmetic.inl
	COMMAND ${AWK} -f compile_arithmetic.awk < dyadic.tpl > arithmetic.c  
	COMMAND ./compile_arithmetic.sh arithmetic.tpl > arithmetic.inl 
  WORKING_DIRECTORY ./src
  COMMENT "Generating arithmetic.c"
)

add_custom_command(
  OUTPUT logical.c logical.inl
	COMMAND ${AWK} -f compile_logical.awk < dyadic.tpl > logical.c  
	COMMAND ./compile_logical.sh logical.tpl > logical.inl 
  WORKING_DIRECTORY ./src
  COMMENT "Generating logical.c"
)


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


add_custom_target(parser_target ALL
    DEPENDS lpl_parser.c lpl_parser.h) 

add_custom_target(lexer_target ALL
    DEPENDS lpl_scanner.h lpl_scanner.c) 

add_custom_target(arithmetic_target ALL
    DEPENDS arithmetic.c arithmetic.inl) 


add_custom_target(logical_target ALL
    DEPENDS logical.c logical.inl) 


include_directories(${PROJECT_SOURCE_DIR}/include)

message("Binary Tree path: ${PROJECT_BINARY_DIR}")

#set(${PROJECT_NAME}_headers ${PROJECT_SOURCE_DIR}/include/col.h)
#set(${PROJECT_NAME}_sources ${PROJECT_SOURCE_DIR}/src/libcol.c )

#add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources} )
#
#install ( TARGETS ${PROJECT_NAME}
#          RUNTIME DESTINATION bin
#          LIBRARY DESTINATION lib
#          ARCHIVE DESTINATION lib/static)

