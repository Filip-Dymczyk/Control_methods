@echo off

:: Format changed files
call code_format 

echo Configuring CMake...
cmake -S . -B builds/test_builds

echo Building project...
cmake --build builds/test_builds --config Release
:: Second build for proper initialization
cmake --build builds/test_builds --config Release

IF %ERRORLEVEL% NEQ 0 (
    echo g++.exe failed! Build aborted.
    exit /b %ERRORLEVEL%
)

echo Build finished successfully!!!