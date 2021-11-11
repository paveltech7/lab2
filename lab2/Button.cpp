#include "Button.h"

void Button::setBox(SMALL_RECT box)
{
	this->box = box;
}

Button::Button(CHAR_INFO* consBuffer, COORD dwStartDrawing, const char title[], COORD bufferSize)
{
	int strSize = strlen(title);
	box = { dwStartDrawing.X, dwStartDrawing.Y, dwStartDrawing.X + (SHORT)strSize + 2, (dwStartDrawing.X + (SHORT)strSize + 2) + (3 * bufferSize.X) };
	for (size_t x = 0; x < strSize; x++)
	{
		consBuffer[dwStartDrawing.Y * dwStartDrawing.X + dwStartDrawing.X + x - 1].Char.UnicodeChar = ' ';
		for (size_t y = 0; y < 3; y++)
		{
			consBuffer[x + (bufferSize.X * dwStartDrawing.Y + dwStartDrawing.X) + (y * bufferSize.X)].Char.UnicodeChar = ' ';
			consBuffer[x + (bufferSize.X * dwStartDrawing.Y + dwStartDrawing.X) + (y * bufferSize.X)].Attributes = BACKGROUND_BLUE |
				BACKGROUND_GREEN | BACKGROUND_RED;
			if (y == 1) {
				consBuffer[x + (bufferSize.X * dwStartDrawing.Y + dwStartDrawing.X) + (y * bufferSize.X)].Char.UnicodeChar = title[x];
			}
		}
	}
}

bool Button::checkClick(COORD click)
{
	for (size_t X = box.Left; X < box.Right; X++)
	{
		for (size_t Y = box.Top; Y < box.Bottom; Y++)
		{
			if (click.X == X && click.Y == Y)
				return true;
		}
	}
	return false;
}