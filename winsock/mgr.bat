@echo off
IF %1.==build. GOTO :build
IF %1.==init. GOTO :init
IF %1.==clean. GOTO :clean

echo Invalid options.
GOTO :end

:init
    @call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"
    SET PATH=%PATH%;C:\Program Files\CMake\bin
    echo Initialized DEV Environment
    IF DEFINED initb (
        GOTO :build
    ) ELSE (
        GOTO :end
    )

:build
    echo Checking for the MSBuild command...
    WHERE msbuild /Q
    IF %ERRORLEVEL% NEQ 0 (
        echo Failed to find MSBuild command. Did you run 'mgr init'?
        GOTO :end
    )

    echo Checking for the CMake command...
    WHERE cmake /Q
    IF %ERRORLEVEL% NEQ 0 (
        echo Failed to find CMake command. Did you run 'mgr init'?
        GOTO :end
    )

    mkdir "%~dp0\build"
    cd "%~dp0\build"
    cmake ..
    msbuild winsock.sln
    move Debug\winsock.exe ..
    cd ..
GOTO :end

:clean
    echo Cleaning...
    if exist *.exe del *.exe
    rmdir build /s /q
GOTO :end

:end
echo END