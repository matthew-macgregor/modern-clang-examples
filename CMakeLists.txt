cmake_minimum_required(VERSION 3.17)
project(modern-clang-examples VERSION 1.0.0)

option(USE_VCPKG "Build projects with vcpkg dependencies" ON)

enable_testing()

add_subdirectory(arrays)
add_subdirectory(conditionals)
add_subdirectory(constants)
add_subdirectory(curl)
add_subdirectory(data-types)
add_subdirectory(functions)
add_subdirectory(input)
add_subdirectory(loops)
add_subdirectory(memory-mgmt)
add_subdirectory(operators)
add_subdirectory(pointers)
add_subdirectory(pointer-practice)
add_subdirectory(storage-class)
add_subdirectory(str-conversion)
add_subdirectory(strings)
add_subdirectory(structs)
add_subdirectory(typedefs-enums)
add_subdirectory(unions)
add_subdirectory(variable-scope)

if (USE_VCPKG)
    add_subdirectory(sqlite3-hello-world)
endif (USE_VCPKG)

if (WIN32)
    add_subdirectory(wininet)
    add_subdirectory(winsock)
    add_subdirectory(win32-color-printf)
endif (WIN32)
