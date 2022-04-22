#!/usr/bin/bash

export CC=/usr/bin/gcc-11
export CXX=/usr/bin/g++-11
export CMAKE_CXX_STANDARD=20

conan build "${PWD}" --build-folder "${PWD}/build"
