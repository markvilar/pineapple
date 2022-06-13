#!/usr/bin/bash

export CC=/usr/bin/gcc-11
export CXX=/usr/bin/g++-11

conan install "${PWD}" \
    --install-folder "${PWD}/build" \
    --build missing \
    --settings build_type="Release" \
    --settings compiler=gcc \
    --settings compiler.version=11 \
    --settings compiler.libcxx=libstdc++11
