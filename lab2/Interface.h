#pragma once
#include <conio.h>
#include <Windows.h>

class Interface
{
private:

public:
	static void setInterface(CHAR_INFO* consBuffer,
		COORD dwBufferSize,
		int horizontalLines);
	static void printString(HANDLE  hConsoleOutput,
		const char title[],
		COORD startCoord);
	static void printArray(HANDLE  hConsoleOutput,
		int* array,
		COORD startCoord,
		int col,
		int length);
};
