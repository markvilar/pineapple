add_library(pineapple STATIC)
add_library(pineapple::pineapple ALIAS pineapple)

find_package(pine REQUIRED)
find_package(msgpack REQUIRED)

if(PINEAPPLE_ENABLE_ZED)
    include("${PROJECT_SOURCE_DIR}/cmake/zed.cmake")
endif()

target_sources(pineapple
    PUBLIC 
        include/pineapple/zed/camera_manager.hpp
        include/pineapple/zed/local_control_layer.hpp
        include/pineapple/zed/protocol.hpp
        include/pineapple/zed/remote_control_layer.hpp
        include/pineapple/zed/types.hpp
        include/pineapple/ui_helpers.hpp
        include/pineapple/utils.hpp
    PRIVATE 
        src/zed/camera_manager.cpp
        src/zed/local_control_layer.cpp
        src/zed/protocol.cpp
        src/zed/remote_control_layer.cpp
        src/ui_helpers.cpp
        src/utils.cpp
    )

# Library include directory
target_include_directories(pineapple
    PUBLIC 
        include
        $<$<BOOL:${PINEAPPLE_ENABLE_ZED}>:${CUDA_INCLUDE_DIRS}>
        $<$<BOOL:${PINEAPPLE_ENABLE_ZED}>:${ZED_INCLUDE_DIRS}>
    PRIVATE 
        src
    )

# Library linking
target_link_libraries(pineapple
    PUBLIC
        pine::pine
        msgpack::msgpack
    PRIVATE 
        $<$<BOOL:${PINEAPPLE_ENABLE_ZED}>:${ZED_LIBS}>
    )

if(MSVC)
    target_compile_definitions(pineapple 
        PUBLIC
            $<$<BOOL:${PINEAPPLE_ENABLE_ZED}>:PINEAPPLE_ENABLE_ZED>
        )
elseif(UNIX)
    target_compile_definitions(pineapple 
        PUBLIC
            $<$<BOOL:${PINEAPPLE_ENABLE_ZED}>:PINEAPPLE_ENABLE_ZED>
        )
endif()

target_compile_definitions(pineapple PUBLIC PRIVATE)
target_compile_features(pineapple PUBLIC cxx_std_17)
target_compile_options(pineapple PUBLIC -std=c++17)

set_target_properties(pineapple PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
