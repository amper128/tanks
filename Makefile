CC = g++
CFLAGS = -g
LDFLAGS = -lGLEW -lGLU -lSDLmain -lSDL

CC2 = i586-mingw32msvc-g++
LDFLAGS2 = -I"/usr/i586-mingw32msvc/include" -L"/usr/i586-mingw32msvc/lib" -lmingw32 -lSDLmain -lSDL -lglew32s -lopengl32 -lgdi32 -lglu32

all:
	$(CC) $(CFLAGS) src/main.cpp -o tanks $(LDFLAGS)
	$(CC2) $(CFLAGS) src/main.cpp -o tanks.exe $(LDFLAGS2)
