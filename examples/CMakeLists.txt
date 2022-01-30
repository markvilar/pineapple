add_executable(record record.cpp)
target_compile_definitions(record PRIVATE)
target_compile_features(record PRIVATE cxx_std_17)
target_compile_options(record PUBLIC -std=c++17)
target_link_libraries(
    record
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    record
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(playground playground.cpp)
target_compile_definitions(playground PRIVATE)
target_compile_features(playground PRIVATE cxx_std_17)
target_compile_options(playground PUBLIC -std=c++17)
target_link_libraries(
    playground
    PRIVATE 
        pine::pine
        pineapple::pineapple)

set_target_properties(
    playground
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
