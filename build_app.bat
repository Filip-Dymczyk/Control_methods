@echo off

:: Format changed files
call code_format_changed 

@echo Application build...

cmake --build build --target main --verbose

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Copying compile_commands.json to project root...
copy /Y build\compile_commands.json compile_commands.json

echo Build finished successfully!!!
