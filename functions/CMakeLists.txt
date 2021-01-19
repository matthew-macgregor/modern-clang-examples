cmake_minimum_required(VERSION 3.0.0)
project(functions VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_test(functions ${PROJECT_NAME})