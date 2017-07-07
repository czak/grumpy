floppy: floppy.cpp
	clang++ -Wall -Wextra -pedantic -std=c++11 -I/usr/include/SDL2 -lSDL2 -o floppy floppy.cpp
