cmake_minimum_required(VERSION 3.16)
project(pineapple VERSION 0.1.1 LANGUAGES CXX)

option(PINEAPPLE_BUILD_EXAMPLES "Build the Pineapple examples." ON)

add_subdirectory(pineapple)
add_subdirectory(apps)

if(PINEAPPLE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
