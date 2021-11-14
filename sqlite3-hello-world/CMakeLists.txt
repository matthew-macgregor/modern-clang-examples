cmake_minimum_required(VERSION 3.0.0)
project(sqlite3-hw VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(unofficial-sqlite3 CONFIG REQUIRED)
add_executable(sqlite3-hw main.c)
target_link_libraries(sqlite3-hw PRIVATE unofficial::sqlite3::sqlite3)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_test(SQLite3_HW sqlite3-hw hello world)
