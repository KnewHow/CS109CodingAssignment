cmake_minimum_required(VERSION 3.0.0)
project(CMakeLists VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CS109 main.cpp common.h
distribution/binomial.h distribution/binomial.cpp 
distribution/geometric.h distribution/geometric.cpp 
distribution/negative_binomial.h distribution/negative_binomial.cpp 
distribution/poisson.h distribution/poisson.cpp
distribution/exponential.h distribution/exponential.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
