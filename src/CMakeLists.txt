# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/ClientPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/DefaultClientPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/InitParametersPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/RecordingParametersPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/RuntimeParametersPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Panels/SensorControllerPanel.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Client.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/ControlLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Image.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/InitParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Messages.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/RecordingParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/RuntimeParameters.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/SensorController.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Server.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ZED/Settings.hpp"
	)

# Library
add_library(Sennet-ZED STATIC
	Panels/ClientPanel.cpp
	Panels/DefaultClientPanel.cpp
	Panels/InitParametersPanel.cpp
	Panels/RecordingParametersPanel.cpp
	Panels/RuntimeParametersPanel.cpp
	Panels/SensorControllerPanel.cpp
	Client.cpp
	ControlLayer.cpp
	Conversion.cpp
	InitParameters.cpp
	RecordingParameters.cpp
	RuntimeParameters.cpp
	SensorController.cpp
	Server.cpp
	Settings.cpp
	"${HEADER_LIST}"
	)

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
