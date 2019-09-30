#include "Globals.h"
#include <windows.h>

long long int Globals::MyGetTime()
{

	LARGE_INTEGER freq;
	LARGE_INTEGER t;
	long long elapsedTime;

	QueryPerformanceFrequency(&freq);

	QueryPerformanceCounter(&t);

	elapsedTime = (t.QuadPart * 1000) / freq.QuadPart;

	return elapsedTime;
}
