# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/SennetZED/ZED/Conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/ZED/IO.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/ZED/Recorder.hpp")

# Library
add_library(SennetZED 
	ZED/Conversion.cpp
	ZED/IO.cpp
	ZED/Recorder.cpp
	"${HEADER_LIST}")
	

# Library include directory
target_include_directories(SennetZED PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/extern/sennet/include"
	${CUDA_INCLUDE_DIRS} 
	${ZED_INCLUDE_DIRS}
	)


# Library linking
target_link_libraries(SennetZED PRIVATE
	${ZED_LIBS}
	)


# Library compilation
target_compile_features(SennetZED PUBLIC cxx_std_17)


# IDEs source
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES "${HEADER_LIST}")
