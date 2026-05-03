@echo off
echo Formatting changed .cpp and .h files...

for /f "delims=" %%f in ('git diff --name-only -- "*.cpp" "*.h"') do (
    set "relative_path=%%~f"
    setlocal enabledelayedexpansion
    set "relative_path=!relative_path:%cd%\=!"

    echo !relative_path! | findstr /I "3rdParty" >nul
    if errorlevel 1 (
        echo !relative_path! | findstr /I "*build*" >nul
        if errorlevel 1 (
            echo Formatting: %%~nxf
            clang-format -i "%%f"
        )
    )
    endlocal
)

echo Formatting completed!
