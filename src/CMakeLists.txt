# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Layers/ControlLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Layers/NetworkLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Layers/SensorLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Layers/StateLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Messages/Request.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Messages/Response.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Parameters/InitParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Parameters/RecordingParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Parameters/RuntimeParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Parameters/Conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Controller.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/IdleNode.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Recorder.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/RecorderNode.hpp"
	)

# Library
add_library(Sennet-ZED STATIC
	Layers/ControlLayer.cpp
	Layers/NetworkLayer.cpp
	Layers/SensorLayer.cpp
	Layers/StateLayer.cpp
	Messages/Request.cpp
	Messages/Response.cpp
	Parameters/InitParameters.cpp
	Parameters/RecordingParameters.cpp
	Parameters/RuntimeParameters.cpp
	Parameters/Conversion.cpp
	Controller.cpp
	IdleNode.cpp
	Recorder.cpp
	RecorderNode.cpp
	"${HEADER_LIST}")

# Library include directory
target_include_directories(Sennet-ZED PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/extern/sennet/include"
	${CUDA_INCLUDE_DIRS} 
	${ZED_INCLUDE_DIRS}
	)

# Library linking
target_link_libraries(Sennet-ZED PRIVATE
	Sennet
	${ZED_LIBS}
	)

# Library compilation
target_compile_features(Sennet-ZED PUBLIC cxx_std_17)

# IDEs source
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES "${HEADER_LIST}")
