cmake_minimum_required(VERSION 3.0.0)
project(CMakeLists VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CS109 main.cpp distribution/binomial.h distribution/binomial.cpp distribution/geometric.h distribution/geometric.cpp common.h)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
