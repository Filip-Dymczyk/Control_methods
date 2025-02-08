@echo off
echo Formatting all .cpp and .h files in the project directory...

for /r %%f in (*.cpp *.h) do (
    set "relative_path=%%~f"
    setlocal enabledelayedexpansion
    set "relative_path=!relative_path:%cd%\=!"

    echo !relative_path! | findstr /I "3rdParty" >nul
    if errorlevel 1 (
        echo !relative_path! | findstr /I "builds" >nul
        if errorlevel 1 (
            echo %%~nxf
            clang-format -i "%%f"
        )
    )
    endlocal
)

echo Formatting completed!
