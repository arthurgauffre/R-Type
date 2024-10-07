#!/bin/bash

rtypeClientBinary=r-type_client
rtypeServerBinary=r-type_server
buildDirectory=build
libDirectory=lib


function clean() {
    rm -f $rtypeClientBinary
    rm -f $rtypeServerBinary
    rm -f build/$rtypeServerBinary
    rm -f build/$rtypeClientBinary
}

function fclean() {
    clean
    rm -rf $buildDirectory
    rm -f $libDirectory/client_components/*.so
    rm -f $libDirectory/shared_components/*.so
    rm -f $libDirectory/server_components/*.so
    rm -f $libDirectory/client_managers/*.so
    rm -f $libDirectory/shared_managers/*.so
    rm -f $libDirectory/server_managers/*.so
    rm -f $libDirectory/client_systems/*.so
    rm -f $libDirectory/shared_systems/*.so
    rm -f $libDirectory/server_systems/*.so
}

args=("$@")

if [ "$#" -gt 1 ]; then
    echo "To much arguments"
    exit 1
fi

if [ "${args[0]}" == "help" ] || [ "${args[0]}" == "h" ]; then
    echo -e "Usage: $0 [Options]\n"
    echo "Options:"
    echo "  none      Compile R-Type server and client."
    echo "  re        Recompile the project from scratch. Use the fclean option."
    echo "  clean     Remove all post-compilation files (binaries...)."
    echo "  fclean    Remove all post-compilation and compilation files (binaries, build dir, .so files,...)."
    exit 0
fi

if [[ "${args[0]}" == "clean" ]] ; then
    clean
elif [[ "${args[0]}" == "fclean" ]] ; then
    fclean
elif [[ "${args[0]}" == "re" ]] ; then
    fclean
    cmake -B $buildDirectory -S .
    cmake --build $buildDirectory -j $(nproc)
else
    cmake -B $buildDirectory -S .
    cmake --build $buildDirectory -j $(nproc)
fi
