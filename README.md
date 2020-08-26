# Sennet ZED module

Module/extension to Sennet with functionality for Stereolabs ZED stereo cameras.
The module includes:
- Wrappers for Stereolabs data structures.
- ZED network messages.
- Intermediate level sensor controller.
- Sensor-, network and control layers for nodes and applications.
- A ZED remote control application as well as a ZED node.

## CMake configuration and building
To build the Sennet ZED moduel, first configure CMake by setting source and build directory: 
``` 
cmake -S . -B build 
```
Then, build the extension by issuing following command:
```
cmake --build build
```
