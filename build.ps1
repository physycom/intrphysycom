mkdir -Force build
cd build

#dynamically linked
cmake .. -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake"

#statically link is broken on Windows due to freeglut library having the wrong name (freeglut_static.lib instead of just freeglut.lib) as of August 2017 - rename manually it if you want to build a static executable
#cmake .. -G "Visual Studio 15" "-DCMAKE_TOOLCHAIN_FILE=$env:WORKSPACE\vcpkg\scripts\buildsystems\vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x86-windows-static"

cmake --build . --config Release
cd ..

