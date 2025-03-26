@echo off
REM Simple build script for the Automaton project on Windows

REM Create and enter build directory
if not exist build mkdir build
cd build

REM Configure and build the project
cmake ..
cmake --build .

echo.
echo Build completed successfully!
echo The executable is located at: %CD%\build\automaton.exe
echo.

pause 