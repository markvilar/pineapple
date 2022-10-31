add_executable(sandbox sandbox.cpp)
target_compile_definitions(sandbox PRIVATE)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_compile_options(sandbox PUBLIC -std=c++17)
target_link_libraries(sandbox PRIVATE pineapple::pineapple)

set_target_properties(sandbox PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
