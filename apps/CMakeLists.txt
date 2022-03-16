add_executable(local_controller local_controller.cpp)
target_compile_definitions(local_controller PRIVATE)
target_compile_features(local_controller PRIVATE cxx_std_17)
target_compile_options(local_controller PUBLIC -std=c++17)
target_link_libraries(
    local_controller
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    local_controller
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(remote_controller remote_controller.cpp)
target_compile_definitions(remote_controller PRIVATE)
target_compile_features(remote_controller PRIVATE cxx_std_17)
target_compile_options(remote_controller PUBLIC -std=c++17)
target_link_libraries(
    remote_controller
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    remote_controller
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
