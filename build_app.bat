@echo off

@echo Application build...
IF NOT EXIST "%cd%\builds\moc_builds" (
    mkdir "%cd%\builds\moc_builds"
)

C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\main_layout.moc.cpp" "%cd%\ApplicationCode\include\main_layout.h"
C:\Qt\6.7.2\mingw_64\bin\moc.exe -o "%cd%\builds\moc_builds\dependency_handler.moc.cpp" "%cd%\ApplicationCode\include\dependency_handler.h"

C:\msys64\ucrt64\bin\g++.exe -fdiagnostics-color=always -g ^
    "%cd%\MainApp\main.cpp" ^
    "%cd%\builds\moc_builds\main_layout.moc.cpp" ^
    "%cd%\builds\moc_builds\dependency_handler.moc.cpp" ^
    -o "%cd%\builds\app_build\app.exe" ^
    -I "%cd%\ApplicationCode\include" ^
    -I "%cd%\LogicCode\include" ^
    -I "%cd%\3rdParty" ^
    -I "C:\Users\User\AppData\Local\Programs\Python\Python311\include" ^
    -I "C:\Users\User\AppData\Local\Programs\Python\Python311\Lib\site-packages\numpy\core\include" ^
    -I "C:\Qt\6.7.2\mingw_64\include" ^
    -L "C:\Qt\6.7.2\mingw_64\lib" ^
    -lQt6Widgets -lQt6Core -lQt6Gui ^
    -L "C:\Users\User\AppData\Local\Programs\Python\Python311\libs" ^
    -lpython311 ^
    -DQT_NO_KEYWORDS

echo Build finished successfully!!!
