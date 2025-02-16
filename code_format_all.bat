@echo off
echo Formatting all .cpp and .h files...

for /r %%f in (*.cpp *.h) do (
    echo Formatting: %%~nxf
    clang-format -i "%%f"
)

echo Formatting completed!