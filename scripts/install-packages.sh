#!/usr/bin/bash

SOURCE_DIR="${PWD}"
PACKAGE_DIR="${PWD}/packages"

BUILD_TYPE="Release"

conan install "${SOURCE_DIR}" \
    --install-folder "${PACKAGE_DIR}" \
    --settings build_type="${BUILD_TYPE}" \
    --build missing
