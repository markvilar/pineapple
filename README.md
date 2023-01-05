# Pineapple

Application built upon pine with various functionality for Stereolabs ZED 
stereo cameras. The following functionality is implemented:
- Intermediate level sensor control which preserves the SDK functionality, while
  allowing concurrency.
- Camera server and message protocol for the ZED.
- Remote control application with a graphical user interface and realtime
  visualization of data.

## Developer workflow

### Dependencies
As Pineapple uses Pine as its backend, clone and install it from
[https://github.com/markvilar/pine]. The easiest way is to package Pine as a
Conan package, using the guide in the repository.

### Building
```shell

# Generate build with CMake (optionally, add -DPINEAPPLE_ENABLE_ZED=OFF to
# disable the functionalities that depend on the ZED SDK)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build
```
