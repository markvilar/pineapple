find_package(pine REQUIRED)

# -----------------------------------------------------------------------------
# Camera server
# -----------------------------------------------------------------------------

if(PINEAPPLE_ENABLE_ZED)
    add_executable(camera_server camera_server.cpp)
    target_compile_definitions(camera_server PRIVATE)
    target_compile_features(camera_server PRIVATE cxx_std_17)
    target_compile_options(camera_server PUBLIC -std=c++17)
    target_link_libraries(camera_server PRIVATE pineapple::pineapple)

    set_target_properties(camera_server PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# -----------------------------------------------------------------------------
# Local controller
# -----------------------------------------------------------------------------

if(PINEAPPLE_ENABLE_ZED)
    add_executable(local_controller local_controller.cpp)
    target_compile_definitions(local_controller PRIVATE)
    target_compile_features(local_controller PRIVATE cxx_std_17)
    target_compile_options(local_controller PUBLIC -std=c++17)
    target_link_libraries(local_controller PRIVATE pineapple::pineapple)

    set_target_properties(local_controller PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    add_custom_command(TARGET local_controller POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${pine_RES_DIRS}"
        "$<TARGET_FILE_DIR:local_controller>/resources")
endif()

# -----------------------------------------------------------------------------
# Remote controller
# -----------------------------------------------------------------------------

add_executable(remote_controller remote_controller.cpp)
target_compile_definitions(remote_controller PRIVATE)
target_compile_features(remote_controller PRIVATE cxx_std_17)
target_compile_options(remote_controller PUBLIC -std=c++17)
target_link_libraries(remote_controller PRIVATE pineapple::pineapple)

set_target_properties(remote_controller PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_command(TARGET remote_controller POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${pine_RES_DIRS}"
    "$<TARGET_FILE_DIR:remote_controller>/resources")
