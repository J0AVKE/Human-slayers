cmake_minimum_required(VERSION 3.23)
project(Shootter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)
add_executable(Shootter src/main.cpp)

target_link_libraries(Shootter PRIVATE SDL3::SDL3)
