find_package(ZED 3 REQUIRED)
find_package(CUDA ${ZED_CUDA_VERSION} REQUIRED)

option(ZED_LINK_SHARED "Link the ZED SDK dynamically." ON)

message(STATUS "Found ZED SDK ${ZED_VERSION} at ${ZED_DIR}.")
message(STATUS "ZED CUDA version: ${ZED_CUDA_VERSION}")

if(NOT ZED_LINK_SHARED AND MSVC)
    message(FATAL_ERROR "ZED SDK static libraries not available on Windows")
endif()

# ZED libraries - static or dynamic linking
if(ZED_LINK_SHARED)
    set(ZED_LIBS
        ${ZED_LIBRARIES}
        ${CUDA_CUDA_LIBRARY}
        ${CUDA_CUDART_LIBRARY}
        ${CUDA_NPP_LIBRARIES_ZED}
        )
else()
    set(ZED_LIBS
        ${ZED_STATIC_LIBRARIES}
        ${CUDA_CUDA_LIBRARY}
        ${CUDA_LIBRARY}
        )
endif()

if(ZED_LINK_SHARED)
    SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})
else()
    SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_LIBRARY})
endif()
