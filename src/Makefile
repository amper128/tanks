CC = g++
CFLAGS = -O3
LDFLAGS = -lGLU -lglut

CC2 = i586-mingw32msvc-g++
LDFLAGS2 = -I"/usr/i586-mingw32msvc/include" -L"/usr/i586-mingw32msvc/lib" -lopengl32 -lgdi32 -lglu32 -lfreeglut

all:
	$(CC) $(CFLAGS) main.cpp -o ../tanks $(LDFLAGS)
	$(CC2) $(CFLAGS) main.cpp -o ../tanks.exe $(LDFLAGS2)
