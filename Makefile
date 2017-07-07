floppy: floppy.cpp screen.cpp screen.h game.cpp game.h
	clang++ -Wall -Wextra -pedantic -std=c++11 -I/usr/include/SDL2 -lSDL2 -lSDL2_image -o floppy floppy.cpp screen.cpp game.cpp
