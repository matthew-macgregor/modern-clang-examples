cmake_minimum_required(VERSION 3.0.0)
project(storage-class VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c external.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(StorageClass ${PROJECT_NAME})