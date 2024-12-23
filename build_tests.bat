@echo off

echo Configuring CMake...
cmake -S . -B builds/test_builds

echo Building project...
cmake --build builds/test_builds --config Release
:: Second build for proper initialization
cmake --build builds/test_builds --config Release

echo Build finished successfully!!!