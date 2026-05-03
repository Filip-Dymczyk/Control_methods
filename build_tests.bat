@echo off

:: Format changed files
call code_format_changed 

echo Building project...
cmake --build build_test --verbose

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Copying compile_commands.json to project root...
copy /Y build_test\compile_commands.json compile_commands.json

echo Build finished successfully!!!
