# Sennet ZED module

Module/extension to Sennet with functionality for Stereolabs ZED stereo cameras.
The module includes:
- Wrappers for Stereolabs data structures.
- ZED network messages.
- Intermediate level sensor controller.
- Sensor-, network and control layers for nodes and applications.
- A ZED remote control application as well as a ZED node.

## CMake configuration and building
Configure CMake:
```
cmake -S . -B build -DBOOST_ROOT=/path/to/boost
```
To build:
```
cmake --build build
```