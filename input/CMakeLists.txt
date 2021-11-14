cmake_minimum_required(VERSION 3.0.0)
project(input VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)
# add_compile_definitions(INPUT_KEYBOARD)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(Input ${PROJECT_NAME})