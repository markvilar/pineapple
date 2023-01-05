cmake_minimum_required(VERSION 3.16)
project(pineapple VERSION 0.1.1 LANGUAGES CXX)

# Project options
option(PINEAPPLE_USE_CONAN "Use Conan for package management." ON)

# Library options
option(PINEAPPLE_ENABLE_ZED "Enable usage of the ZED SDK." ON)

# Build options
option(PINEAPPLE_BUILD_EXAMPLES "Build the Pineapple examples." ON)


if(PINEAPPLE_USE_CONAN)
    if(CONAN_EXPORTED)
        include(conanbuildinfo.cmake)
        conan_basic_setup()
    else()
        include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan.cmake")
        conan_cmake_run(CONANFILE "${CMAKE_CURRENT_SOURCE_DIR}/conanfile.py"
            BASIC_SETUP 
            CMAKE_TARGETS 
            BUILD missing
        )
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endif()

add_subdirectory(bin)
add_subdirectory(src)

if(PINEAPPLE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
