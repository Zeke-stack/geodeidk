@echo off
echo ========================================
echo FakeGDMod v2.5.0 - Build Script
echo ========================================
echo.

REM Check if Geode CLI exists
if not exist "C:\Users\zekef\Downloads\gdsdk\geode.exe" (
    echo ERROR: Geode CLI not found!
    echo Expected location: C:\Users\zekef\Downloads\gdsdk\geode.exe
    pause
    exit /b 1
)

REM Check if CMake is available
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found in PATH!
    echo.
    echo Please install CMake from: https://cmake.org/download/
    echo Make sure to check "Add CMake to system PATH" during installation
    echo.
    pause
    exit /b 1
)

echo Building mod with Geode CLI...
echo.

C:\Users\zekef\Downloads\gdsdk\geode.exe build

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo BUILD SUCCESSFUL!
    echo ========================================
    echo.
    echo Your compiled mod is in the 'build' folder
    echo Look for: FakeGDMod.geode
    echo.
) else (
    echo.
    echo ========================================
    echo BUILD FAILED!
    echo ========================================
    echo Check the errors above
    echo.
)

pause
