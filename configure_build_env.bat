@echo off

IF EXIST "%cd%\build" (
    rmdir /s /q "%cd%\build"
)

IF EXIST "%cd%\build_debug" (
    rmdir /s /q "%cd%\build_debug"
)

IF EXIST "%cd%\build_test" (
    rmdir /s /q "%cd%\build_test"
)

:: =========================
:: Release build (app only)
:: =========================
cmake -S . -B build -G "MinGW Makefiles" ^
    -DCMAKE_MAKE_PROGRAM=D:/Qt/Tools/mingw1120_64/bin/mingw32-make.exe ^
    -DCMAKE_PREFIX_PATH=D:/Qt/6.7.2/mingw_64 ^
    -DCMAKE_C_COMPILER=D:/Qt/Tools/mingw1120_64/bin/gcc.exe ^
    -DCMAKE_CXX_COMPILER=D:/Qt/Tools/mingw1120_64/bin/g++.exe ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DBUILD_TESTS=OFF

:: =========================
:: Debug build (app only)
:: =========================
cmake -S . -B build_debug -G "MinGW Makefiles" ^
    -DCMAKE_MAKE_PROGRAM=D:/Qt/Tools/mingw1120_64/bin/mingw32-make.exe ^
    -DCMAKE_PREFIX_PATH=D:/Qt/6.7.2/mingw_64 ^
    -DCMAKE_C_COMPILER=D:/Qt/Tools/mingw1120_64/bin/gcc.exe ^
    -DCMAKE_CXX_COMPILER=D:/Qt/Tools/mingw1120_64/bin/g++.exe ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DBUILD_TESTS=OFF

:: =========================
:: Test build (no app)
:: =========================
cmake -S . -B build_test -G "MinGW Makefiles" ^
    -DCMAKE_MAKE_PROGRAM=D:/Qt/Tools/mingw1120_64/bin/mingw32-make.exe ^
    -DCMAKE_PREFIX_PATH=D:/Qt/6.7.2/mingw_64 ^
    -DCMAKE_C_COMPILER=D:/Qt/Tools/mingw1120_64/bin/gcc.exe ^
    -DCMAKE_CXX_COMPILER=D:/Qt/Tools/mingw1120_64/bin/g++.exe ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DBUILD_TESTS=ON 