#pragma once

#ifdef __APPLE__

#endif

#ifdef __MINGW32__
//если вдруг случилось так, что винда...
#include <windows.h>
#endif

#ifdef __linux
//варианты для linux
#include <sys/time.h>
#include <cstdio>
#endif

#include <unistd.h>

typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned int uint;

long int MilliSecs();

void Delay( int millis );

