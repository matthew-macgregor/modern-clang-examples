cmake_minimum_required(VERSION 3.0.0)
project(w32-colorconsole VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(w32-colorconsole main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(W32_Color_Console w32-colorconsole)