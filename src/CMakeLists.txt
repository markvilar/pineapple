# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Layers/ControlLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Layers/DisplayLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Layers/NetworkLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Layers/SensorLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Messages/Request.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Messages/Response.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Primitives/Conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Primitives/IO.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Primitives/Settings.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Controller.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/IdleNode.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/Recorder.hpp"
	"${PROJECT_SOURCE_DIR}/include/SennetZED/RecorderNode.hpp"
	)

# Library
add_library(SennetZED STATIC
	Layers/ControlLayer.cpp
	Layers/DisplayLayer.cpp
	Layers/NetworkLayer.cpp
	Layers/SensorLayer.cpp
	Messages/Request.cpp
	Messages/Response.cpp
	Primitives/Conversion.cpp
	Primitives/IO.cpp
	Primitives/Settings.cpp
	Controller.cpp
	IdleNode.cpp
	Recorder.cpp
	RecorderNode.cpp
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
	Sennet
	${ZED_LIBS}
	)

# Library compilation
target_compile_features(SennetZED PUBLIC cxx_std_17)

# IDEs source
source_group(TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES "${HEADER_LIST}")
