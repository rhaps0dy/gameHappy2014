default: all
.PHONY: default

all:
	g++ -g -o main main.cpp Player.cpp Timer.cpp World.cpp utils.cpp Rectangle.cpp -I/usr/include/SDL -lSDL -lSDL_image -lSDL_mixer -lm -lstdc++
.PHONY: all

level:
	cd resources && python feslevel.py
.PHONY: level

windows:
	x86_64-w64-mingw32-g++ -o main.exe main.cpp Player.cpp Timer.cpp World.cpp utils.cpp Rectangle.cpp -lSDL -lSDL_image -lSDL_mixer -lm -lstdc++ -I/usr/x86_64-w64-mingw32/include/SDL -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib

.PHONY: windows
