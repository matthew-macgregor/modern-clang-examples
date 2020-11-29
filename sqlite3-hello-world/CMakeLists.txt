cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(unofficial-sqlite3 CONFIG REQUIRED)
add_executable(main main.c)
target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(Runs main hello world)

