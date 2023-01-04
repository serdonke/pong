#!/bin/sh

# Build and run the file

function build() {
    gcc pong.c -o ./build/pong -Wall -I. -I../raylib/src -L. -L../raylib/src -lraylib -lGL -lc -lm -lpthread -ldl -lrt -lX11 && ./build/pong
}

if [ -f CMakeLists.txt ]; then
    cmake -G "Unix Makefiles" -S . -B cmake-build
    cp ./res ./cmake-build
    cmake --build cmake-build
    if [ -x ./cmake-build/pong ]; then
        ./cmake-build/pong
    fi
else
    if [ -d ./build ]; then
        build
    else
        mkdir build && cp res build && build
    fi
fi