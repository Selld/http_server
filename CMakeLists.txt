cmake_minimum_required(VERSION 2.8)

set(GCC_COVERAGE_COMPILE_FLAGS "--std=c++11")
#set(GCC_COVERAGE_LINK_FLAGS    "-lboost_system -lpthread")
set(CMAKE_BINARY_DIR bin)
set(SOURCES connectionhandler.cpp http_request.cpp http_response.cpp httpserver.cpp main.cpp)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

add_executable(final ${SOURCES})

target_link_libraries(final pthread boost_system)