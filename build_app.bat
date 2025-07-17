@echo off

:: Format changed files
call code_format_changed 

@echo Application build...
IF NOT EXIST "%cd%\builds" (
    mkdir "%cd%\builds"
)

IF NOT EXIST "%cd%\builds\moc_builds" (
    mkdir "%cd%\builds\moc_builds"
)

IF NOT EXIST "%cd%\builds\app_build" (
    mkdir "%cd%\builds\app_build"
)

C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\main_widget.moc.cpp" "%cd%\ApplicationCode\include\main_widget.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\dependency_handler.moc.cpp" "%cd%\ApplicationCode\include\dependency_handler.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\clickable_line_edit.moc.cpp" "%cd%\ApplicationCode\include\clickable_line_edit.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\inputs_parser.moc.cpp" "%cd%\ApplicationCode\include\inputs_parser.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\simulator.moc.cpp" "%cd%\ApplicationCode\include\simulator.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\plotter.moc.cpp" "%cd%\ApplicationCode\include\plotter.h"

C:\msys64\mingw64\bin\g++.exe -fdiagnostics-color=always -g -static ^
    "%cd%\MainApp\main.cpp" ^
    "%cd%\builds\moc_builds\main_widget.moc.cpp" ^
    "%cd%\builds\moc_builds\dependency_handler.moc.cpp" ^
    "%cd%\builds\moc_builds\clickable_line_edit.moc.cpp" ^
    "%cd%\builds\moc_builds\inputs_parser.moc.cpp" ^
    "%cd%\builds\moc_builds\simulator.moc.cpp" ^
    "%cd%\builds\moc_builds\plotter.moc.cpp" ^
    -o "%cd%\builds\app_build\app.exe" ^
    -I "%cd%\ApplicationCode\include" ^
    -I "%cd%\LogicCode\include" ^
    -I "%cd%\3rdParty" ^
    -I "C:\Qt\6.7.2\mingw_64\include" ^
    -L "C:\Qt\6.7.2\mingw_64\lib" ^
    -lQt6Widgets -lQt6Core -lQt6Gui -lQt6Charts^
    -DQT_NO_KEYWORDS

IF %ERRORLEVEL% NEQ 0 (
    echo g++.exe failed! Build aborted.
    exit /b %ERRORLEVEL%
)

echo Build finished successfully!!!
