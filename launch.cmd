@echo off
setlocal

:: Definir les variables
set rtypeClientBinary=r-type_client.exe
set rtypeServerBinary=r-type_server.exe
set buildDirectory=build
set libDirectory=lib

echo Initialisation du script...

:: Gerer les arguments
echo [DEBUG] Arguments reçus : %*
if "%~1"=="" (
    echo [DEBUG] Aucune option specifiee, compilation par defaut...
    call :compile
    goto :eof
) else (
    echo [DEBUG] Argument reçu : %1
)

if /I "%~1"=="help" (
    echo Utilisation : %~n0 [Options]
    echo.
    echo Options :
    echo   none      Compile le serveur et le client R-Type.
    echo   re        Recompile le projet a partir de zero (fclean inclus).
    echo   clean     Supprime tous les fichiers de post-compilation (binaires...).
    echo   fclean    Supprime tous les fichiers de compilation et post-compilation (binaires, dossier build, fichiers .dll,...).
    pause
    goto :eof
) else if /I "%~1"=="clean" (
    call :clean
    echo [DEBUG] Fonction clean appelee.
    goto :eof  :: Ajout de goto pour eviter d'executer d'autres blocs
) else if /I "%~1"=="fclean" (
    call :fclean
    echo [DEBUG] Fonction fclean appelee.
    goto :eof  :: Ajout de goto pour eviter d'executer d'autres blocs
) else if /I "%~1"=="re" (
    echo [DEBUG] Fonction re appelee, nettoyage et compilation...
    call :fclean
    call :compile
    echo [DEBUG] Fonction compile appelee après fclean.
    goto :eof  :: Ajout de goto pour eviter d'executer d'autres blocs
) else (
    echo Option invalide : %1
    pause
    goto :eof  :: Ajout de goto pour eviter d'executer d'autres blocs
)

:: Fonction clean
:clean
echo [DEBUG] Entree dans la fonction clean
echo Suppression des fichiers de build...
del /Q %rtypeClientBinary% 2>nul
del /Q %rtypeServerBinary% 2>nul
del /Q %buildDirectory%\%rtypeClientBinary% 2>nul
del /Q %buildDirectory%\%rtypeServerBinary% 2>nul
echo Fin de la suppression des fichiers de build.
goto :eof

:: Fonction fclean
:fclean
echo [DEBUG] Entree dans la fonction fclean
echo Suppression complète des fichiers et du dossier de build...
call :clean
rmdir /S /Q %buildDirectory% 2>nul
del /Q %libDirectory%\client_systems\*.dll 2>nul
del /Q %libDirectory%\shared_systems\*.dll 2>nul
del /Q %libDirectory%\server_systems\*.dll 2>nul
del /Q %libDirectory%\shared_entity\*.dll 2>nul
echo Fin de la suppression complète.
goto :eof

:: Fonction compile
:compile
echo [DEBUG] Entree dans la fonction compile
echo Mise a jour des sous-modules Git...
git submodule update --init --recursive
if errorlevel 1 (
    echo Erreur lors de la mise a jour des sous-modules Git.
    pause
    goto :eof
)

echo Execution de CMake...
cmake -B %buildDirectory% -S .
if errorlevel 1 (
    echo Erreur lors de l'execution de CMake.
    pause
    goto :eof
)

echo Construction du projet avec CMake...
cmake --build %buildDirectory% -- /p:VcpkgEnableManifest=true
if errorlevel 1 (
    echo Erreur lors de la construction avec CMake.
    pause
    goto :eof
)
echo Compilation terminee.
goto :eof

echo [DEBUG] Fin du script.
endlocal
