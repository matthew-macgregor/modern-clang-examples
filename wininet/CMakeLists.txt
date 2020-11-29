cmake_minimum_required(VERSION 3.10)

project(wininet)

add_executable(
    wininet
    wininet-main.c 
    args.c
    utils.c
)