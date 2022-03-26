add_library(pineapple STATIC)
add_library(pineapple::pineapple ALIAS pineapple)

option(ZED_LINK_SHARED "Link with the ZED SDK shared executable" ON)

find_package(pine REQUIRED)
find_package(Protobuf REQUIRED)
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
        include/Pineapple/CameraControls.hpp
        include/Pineapple/CameraNode.hpp
        include/Pineapple/LocalControlLayer.hpp
        include/Pineapple/Messages.hpp
        include/Pineapple/RecordManager.hpp
        include/Pineapple/RemoteControlLayer.hpp
        include/Pineapple/SensorData.hpp
        include/Pineapple/UserInterface.hpp
        include/Pineapple/Utils.hpp
    PRIVATE 
        src/CameraNode.cpp
        src/LocalControlLayer.cpp
        src/RecordManager.cpp
        src/RemoteControlLayer.cpp
        src/UserInterface.cpp
        src/Utils.cpp)

# Library include directory
target_include_directories(pineapple
    PUBLIC 
        include
        ${ZED_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
    PRIVATE 
        src)

# Library linking
target_link_libraries(pineapple
    PUBLIC
        pine::pine
        protobuf::protobuf
    PRIVATE 
        ${ZED_LIBS})

if(MSVC)
    target_compile_definitions(pineapple PUBLIC)
elseif(UNIX)
    target_compile_definitions(pineapple PUBLIC)
endif()

target_compile_definitions(pineapple PUBLIC PRIVATE)
target_compile_features(pineapple PUBLIC cxx_std_17)
target_compile_options(pineapple PUBLIC -std=c++17)

set_target_properties(pineapple PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
