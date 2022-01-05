add_executable(controller controller.cpp)
target_compile_definitions(controller PRIVATE)
target_compile_features(controller PRIVATE cxx_std_17)
target_compile_options(controller PUBLIC -std=c++17)
target_link_libraries(
    controller
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    controller
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(node node.cpp)
target_compile_definitions(node PRIVATE)
target_compile_features(node PRIVATE cxx_std_17)
target_compile_options(node PUBLIC -std=c++17)
target_link_libraries(
    node
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    node
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
