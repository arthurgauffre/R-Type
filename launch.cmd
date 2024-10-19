@echo off
setlocal

:: Set variables
set rtypeClientBinary=r-type_client.exe
set rtypeServerBinary=r-type_server.exe
set buildDirectory=build
set libDirectory=lib

:: Clean function
:clean
del /Q %rtypeClientBinary% 2>nul
del /Q %rtypeServerBinary% 2>nul
del /Q %buildDirectory%\%rtypeClientBinary% 2>nul
del /Q %buildDirectory%\%rtypeServerBinary% 2>nul
goto :eof

:: Fclean function
:fclean
call :clean
rmdir /S /Q %buildDirectory% 2>nul
del /Q %libDirectory%\client_systems\*.dll 2>nul
del /Q %libDirectory%\shared_systems\*.dll 2>nul
del /Q %libDirectory%\server_systems\*.dll 2>nul
del /Q %libDirectory%\shared_entity\*.dll 2>nul
goto :eof

:: Functions Declarations
:whichCMake
	cmake --version || EXIT /B 1
EXIT /B 0

:whichMinGW
	g++ --version || EXIT /B 1
EXIT /B 0

:whichVisualStudio
    if EXIST "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" (
        EXIT /B 0
    ) else (
        EXIT /B 1
    )
EXIT /B 0


:: Check for MinGW
CALL :whichMinGW
SET MinGWPath=%ERRORLEVEL%
if %MinGWPath%==1 (
    echo Please install MinGW first
    EXIT /B 1
) else (
    echo MinGW is installed
)

:: Check for CMake
CALL :whichCMake
SET cmakePath=%ERRORLEVEL%
if %cmakePath%==1 (
    echo Please install cmake first
    EXIT /B 1
) else (
    echo CMake is installed
)


:: Check for Visual Studio
CALL :whichVisualStudio
SET VisualStudioPath=%ERRORLEVEL%
if %VisualStudioPath%==1 (
    echo Please install "Visual Studio 2022" first
    EXIT /B 1
) else (
    echo Visual Studio is installed
)

:: Argument handling
set args=%*
if not "%args%"=="" (
    if not "%args:help=%"=="%args%" (
        echo Usage: %~n0 [Options]
        echo Options:
        echo   none      Compile R-Type server and client.
        echo   re        Recompile the project from scratch. Use the fclean option.
        echo   clean     Remove all post-compilation files (binaries...).
        echo   fclean    Remove all post-compilation and compilation files (binaries, build dir, .dll files,...).
        exit /b 0
    )
)


:: Execute commands based on arguments
if "%args%"=="clean" (
    call :clean
) else if "%args%"=="fclean" (
    call :fclean
) else if "%args%"=="re" (
    call :fclean
    cmake -B %buildDirectory% -S .
    cmake --build %buildDirectory% -- /maxcpucount
) else (
    cmake -B %buildDirectory% -S .
    cmake --build %buildDirectory% -- /maxcpucount
)

endlocal
