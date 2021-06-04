# Project
cmake_minimum_required(VERSION 3.16)
project(SennetZED VERSION 1.0 LANGUAGES CXX)

# Build configurations
add_compile_definitions(SN_DEBUG)
add_compile_definitions(SN_PLATFORM_LINUX)

# Options
option(ZED_LINK_SHARED "Link with the ZED SDK shared executable" ON)

# If main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# Let's ensure -std=c++xx instead of -std=g++xx
	set(CMAKE_CXX_EXTENSIONS OFF)
	# Support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	# Enable testing
	include(CTest)
endif()

# Find packages
find_package(Git QUIET)
find_package(ZED 3 REQUIRED)
find_package(CUDA REQUIRED)

message(STATUS "Found ZED SDK ${ZED_VERSION} at ${ZED_DIR}. ZED CUDA version:
	${ZED_CUDA_VERSION}")

if(NOT ZED_LINK_SHARED AND MSVC)
    message(FATAL_ERROR "ZED_LINK_SHARED OFF : ZED SDK static libraries not available on Windows")
endif()

# ZED libraries - static or dynamic linking
if(ZED_LINK_SHARED)
    	SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} 
		${CUDA_CUDART_LIBRARY} ${CUDA_NPP_LIBRARIES_ZED})
else()
    	SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} 
		${CUDA_LIBRARY})
endif()


# Git submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
    	option(GIT_SUBMODULE "Check submodules during build" ON)
    	if(GIT_SUBMODULE)
        	message(STATUS "Submodule update")
        	execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
				--recursive WORKING_DIRECTORY 
				${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE 
				GIT_SUBMOD_RESULT)
        	if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            	message(FATAL_ERROR "git submodule update --init failed "
				"with ${GIT_SUBMOD_RESULT}, please checkout "
				"submodules.")
        	endif()
    	endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/Sennet/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Library source code
add_subdirectory(src)

# Executable code - compile if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(apps)
endif()

# External libraries
add_subdirectory(extern/Sennet)
