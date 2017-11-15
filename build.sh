#!/bin/bash

mkdir -p build
cd build
cmake .. "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=${WORKSPACE}\sysconfig\cmake\physycom_toolchain.cmake" 
#cmake .. -DINTERNET_DISABLED:BOOL=TRUE "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=${WORKSPACE}\sysconfig\cmake\physycom_toolchain.cmake" 
cmake --build . 
cd ..
