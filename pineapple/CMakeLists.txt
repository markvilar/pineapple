add_library(pineapple STATIC)
add_library(pineapple::pineapple ALIAS pineapple)

option(ZED_LINK_SHARED "Link with the ZED SDK shared executable" ON)

find_package(pine REQUIRED)
find_package(ZED 3 REQUIRED)
find_package(CUDA REQUIRED)

message(STATUS "Found ZED SDK ${ZED_VERSION} at ${ZED_DIR}. ZED CUDA version:
	${ZED_CUDA_VERSION}")

if(NOT ZED_LINK_SHARED AND MSVC)
    message(FATAL_ERROR "ZED_LINK_SHARED OFF : ZED SDK static libraries not "
        "available on Windows")
endif()

# ZED libraries - static or dynamic linking
if(ZED_LINK_SHARED)
    set(ZED_LIBS
        ${ZED_LIBRARIES}
        ${CUDA_CUDA_LIBRARY}
        ${CUDA_CUDART_LIBRARY}
        ${CUDA_NPP_LIBRARIES_ZED})
else()
    set(ZED_LIBS
        ${ZED_STATIC_LIBRARIES}
        ${CUDA_CUDA_LIBRARY}
        ${CUDA_LIBRARY})
endif()

target_sources(pineapple
    PUBLIC 
        include/Pineapple/Zed/CameraNode.hpp
        include/Pineapple/Zed/LocalControlLayer.hpp
        include/Pineapple/Zed/Protocol.hpp
        include/Pineapple/Zed/RecordManager.hpp
        include/Pineapple/Zed/RemoteControlLayer.hpp
        include/Pineapple/Zed/Types.hpp
        include/Pineapple/Message.hpp
        include/Pineapple/Serialization.hpp
        include/Pineapple/UiHelpers.hpp
        include/Pineapple/Utils.hpp
    PRIVATE 
        src/Zed/CameraNode.cpp
        src/Zed/LocalControlLayer.cpp
        src/Zed/RecordManager.cpp
        src/Zed/RemoteControlLayer.cpp
        src/UiHelpers.cpp
        src/Utils.cpp)

# Library include directory
target_include_directories(pineapple
    PUBLIC 
        include
        ${CUDA_INCLUDE_DIRS}
        ${ZED_INCLUDE_DIRS}
    PRIVATE 
        src)

# Library linking
target_link_libraries(pineapple
    PUBLIC
        pine::pine
    PRIVATE 
        ${ZED_LIBS})

if(MSVC)
    target_compile_definitions(pineapple PUBLIC)
elseif(UNIX)
    target_compile_definitions(pineapple PUBLIC)
endif()

message(STATUS "Pineapple compiler")
message(STATUS "${CMAKE_CXX_COMPILER_ID}")
message(STATUS "${CMAKE_CXX_COMPILER_VERSION}")

target_compile_definitions(pineapple PUBLIC PRIVATE)
target_compile_features(pineapple PUBLIC cxx_std_17)
target_compile_options(pineapple PUBLIC -std=c++17)

set_target_properties(pineapple PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
