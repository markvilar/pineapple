#!/usr/bin/bash

SOURCE_DIR="${PWD}"
BUILD_DIR="${SOURCE_DIR}/build/"
PACKAGE_DIR="${SOURCE_DIR}/../pine-packages/"

GENERATOR="Ninja"
BUILD_TYPE="Debug"
CXX_COMPILER="clang++-12"

if [ ! -d ${BUILD_DIR} ]; then
    mkdir -p ${BUILD_DIR}

    export CMAKE_GENERATOR="${GENERATOR}"
    export CMAKE_BUILD_TYPE="${BUILD_TYPE}"
    export CMAKE_CXX_COMPILER="${CXX_COMPILER}"

    cmake -S "${SOURCE_DIR}" -B "${BUILD_DIR}" \
        -D CMAKE_MODULE_PATH="${PACKAGE_DIR}"
fi

cmake --build ${BUILD_DIR}
