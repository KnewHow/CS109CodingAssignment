cmake_minimum_required(VERSION 3.0.0)
project(CS109 VERSION 0.1.0)

include(CTest)
enable_testing()



include_directories(src/bat.h)

file(GLOB SOURCES
"src/*.h"
"src/*.cpp"
)

add_executable(${PROJECT_NAME} src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
