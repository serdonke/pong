CC=gcc
LDLIBS=-static-libgcc -lraylib -lopengl32 -lgdi32 -lwinmm
INCLUDEPATH=-I. -I../raylib/src
LIBPATH=-L. -L../raylib/src

all:clean build
	./build/pong.exe

build:
	mkdir build
	$(CC) pong.c -o ./build/pong $(INCLUDEPATH) $(LIBPATH) $(LDLIBS)

rebuild-raylib:
	make -C ../raylib/src clean all

clean:
	rm build/pong.exe
	rmdir build
