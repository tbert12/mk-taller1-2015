cmake_minimum_required(VERSION 2.6)
project(mortal-kombat C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(json libs/jsoncpp.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB mk-files
        "src/controller/*.h"
        "src/controller/*.cpp"
        "src/model/personajes/*.h"
        "src/model/personajes/*.cpp"
        "src/model/*.h"
        "src/model/*.cpp"
        "src/view/*.h"
        "src/view/*.cpp"
        )

add_executable(mk
        ${mk-files}
        )

target_link_libraries(mk json)
target_link_libraries(mk SDL2 SDL2_image SDL2_ttf SDL2_mixer)