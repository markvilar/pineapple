# Project
cmake_minimum_required(VERSION 3.13...3.16)
project(SennetZED VERSION 1.0 LANGUAGES CXX)

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
message(STATUS "Found ZED SDK ${ZED_VERSION} at ${ZED_DIR}. ZED CUDA version:
	${ZED_CUDA_VERSION}")
find_package(CUDA REQUIRED)

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

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/sennet/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Library source code
add_subdirectory(src)

# Executable source code
add_subdirectory(apps)

# External libraries
add_subdirectory(extern/sennet)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
	add_subdirectory(tests)
endif()
