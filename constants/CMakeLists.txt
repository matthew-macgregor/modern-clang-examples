cmake_minimum_required(VERSION 3.0.0)
project(constants VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(Constants ${PROJECT_NAME})