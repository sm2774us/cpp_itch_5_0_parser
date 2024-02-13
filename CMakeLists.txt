cmake_minimum_required(VERSION 2.8)

project(itch_parser)

set(ITCH_PARSER_VERSION "0.0.1")

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generate API reference with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)

find_package(Boost REQUIRED)

find_package(Curses)

find_package(PkgConfig)

pkg_check_modules(LIBUV REQUIRED libuv>=1.0)
include_directories(${LIBUV_INCLUDE_DIRS})

include_directories("include")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

set(CMAKE_C_FLAGS "-Iinclude -Wall -O3 -g -std=gnu11")
set(CMAKE_CXX_FLAGS "-Iinclude -Wall -O3 -g -std=c++14")

set(cHeaders
    include/itch-parser-c/itch_parser.h
)

configure_file("itch_parser.pc.in" "itch_parser.pc" @ONLY)

install(FILES ${cHeaders} DESTINATION include/itch-parser-c)
install(TARGETS itch_parser_incl DESTINATION lib)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/itch_parser.pc"
              DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

add_executable(itch_parser src/itch_parser.cpp)
target_link_libraries(itch_parser itch_parser_incl ${LIBUV_LIBRARIES})
