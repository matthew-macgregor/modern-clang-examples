cmake_minimum_required(VERSION 3.0.0)
project(curl-simple VERSION 0.1.0 LANGUAGES C)
find_package(CURL)

include(CTest)
enable_testing()

set(CMAKE_C_STANDARD 17)

add_executable(curl-simple simple.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CURL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
                        CURL::libcurl
                        ${CURL_LIBRARIES})

add_test(Curl_Simple curl-simple)