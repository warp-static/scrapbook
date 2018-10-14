cmake_minimum_required(VERSION 2.6)
project(scrapbook)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake}")

find_package(OpenGL)

find_package(SDL2)

find_package(GLEW)

find_package(ASSIMP)

include_directories(${SDL2_INCLUDE_DIRS} include)

add_subdirectory(Disaster)