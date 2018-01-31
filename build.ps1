#!/usr/bin/env powershell

mkdir -Force build
cd build

#FLTK are broken as of november 2017 if you use dynamic linking
cmake -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows-static" "-DCMAKE_BUILD_TYPE=Release" ..
cmake --build . --config Release --target install

cd ..
