#!/usr/bin/env powershell

mkdir -Force build
cd build

#FLTK are broken as of november 2017 if you use dynamic linking
#So we have to use a static triplet for vcpkg
cmake .. -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$env:WORKSPACE\sysconfig\cmake\physycom_toolchain.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows-static" "-DCMAKE_BUILD_TYPE=Release"

cmake --build . --config Release

cd ..
