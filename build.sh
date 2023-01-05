#!/bin/sh


# helper functions
# fetch raylib (requires git)
function cloneraylib() {
    if [ -d deps ]; then
        git clone https://github.com/raysan5/raylib.git --depth=1 ./deps
    else    
        mkdir deps && \
        git clone https://github.com/raysan5/raylib.git --depth=1 ./deps
    fi
}
# Build raylib
function buildraylib() {
    if ! [ -f ./deps/src/libraylib.a ]; then
        make -C ./deps/src clean all
    fi
}
# Build the game
function build() {
    gcc pong.c -o ./build/pong -Wall -I. -I./deps/src/ -L. -L./deps/src/ -lraylib -lGL -lc -lm -lpthread -ldl -lrt -lX11 && \
    ./build/pong
}



# Build and run the game

if [ -f CMakeLists.txt ] && [ -x $(which cmake) ]; then
    echo "Using cmake"
    cmake -G "Unix Makefiles" -S . -B cmake-build
    cmake --build cmake-build
    if [ -x ./cmake-build/pong ]; then
        ./cmake-build/pong
    fi
else
    echo "Using git, gcc and make, If the build fails download those with your package manager"
    if ! [ -d ./deps/src/ ]; then
        cloneraylib && buildraylib
    fi
    if [ -d ./build ]; then
        build
    else
        mkdir build && build
    fi
fi
