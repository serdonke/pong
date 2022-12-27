#!/bin/sh

# Build and run the file

function build() {
    gcc pong.c -o ./build/pong -Wall -I. -I../raylib/src -L. -L../raylib/src -lraylib -lGL -lc -lm -lpthread -ldl -lrt -lX11 && ./build/pong
}

if [ -d ./build ]; then
    build
else
    mkdir build && build
fi