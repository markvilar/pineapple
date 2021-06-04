# Controller
add_executable(Controller Controller.cpp)
target_compile_features(Controller PRIVATE cxx_std_17)
target_link_libraries(Controller PRIVATE Sennet Sennet-ZED)

# ZEDNode
add_executable(ZEDNode ZEDNode.cpp)
target_compile_features(ZEDNode PRIVATE cxx_std_17)
target_link_libraries(ZEDNode PRIVATE Sennet Sennet-ZED)

# ZEDRecord
add_executable(ZEDRecord ZEDRecord.cpp)
target_compile_features(ZEDRecord PRIVATE cxx_std_17)
target_link_libraries(ZEDRecord PRIVATE Sennet Sennet-ZED)
