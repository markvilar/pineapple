add_executable(topside_app topside_app.cpp)
target_compile_definitions(topside_app PRIVATE)
target_compile_features(topside_app PRIVATE cxx_std_17)
target_compile_options(topside_app PUBLIC -std=c++17)
target_link_libraries(
    topside_app
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    topside_app
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(camera_node camera_node.cpp)
target_compile_definitions(camera_node PRIVATE)
target_compile_features(camera_node PRIVATE cxx_std_17)
target_compile_options(camera_node PUBLIC -std=c++17)
target_link_libraries(
    camera_node
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    camera_node
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
