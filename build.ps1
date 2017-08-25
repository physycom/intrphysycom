mkdir -Force build
cd build

#dynamic linked
cmake .. -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake"

#static link is broken on Windows due to freeglut library having the wrong name (freeglut_static.lib instead of just freeglut.lib) as of August 2017
#cmake .. -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows-static"

cmake --build . --target install --config Release
cd ..

