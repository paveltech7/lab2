#pragma once
#include <Windows.h>

class Button
{
private:
	SMALL_RECT box;

public:
	void setBox(SMALL_RECT box);
	Button(CHAR_INFO* consBuffer, COORD dwStartDrawing, const char title[], COORD bufferSize);
	bool checkClick(COORD click);
};
