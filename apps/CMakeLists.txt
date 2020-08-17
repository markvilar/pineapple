# IdleNodeOne
add_executable(IdleNode IdleNode.cpp)
target_compile_features(IdleNode PRIVATE cxx_std_17)
target_link_libraries(IdleNode PRIVATE Sennet SennetZED)

# Sandbox
add_executable(Sandbox Sandbox.cpp)
target_compile_features(Sandbox PRIVATE cxx_std_17)
target_link_libraries(Sandbox PRIVATE Sennet SennetZED)

# ZEDControl
add_executable(ZEDControl ZEDControl.cpp)
target_compile_features(ZEDControl PRIVATE cxx_std_17)
target_link_libraries(ZEDControl PRIVATE Sennet SennetZED)

# ZEDNodeOne
add_executable(ZEDNode ZEDNode.cpp)
target_compile_features(ZEDNode PRIVATE cxx_std_17)
target_link_libraries(ZEDNode PRIVATE Sennet SennetZED)

# ZEDSandbox
add_executable(ZEDSandbox ZEDSandbox.cpp)
target_compile_features(ZEDSandbox PRIVATE cxx_std_17)
target_link_libraries(ZEDSandbox PRIVATE Sennet SennetZED)
