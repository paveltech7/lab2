#include "Interface.h"
#include <iostream>

void Interface::setInterface(CHAR_INFO* consBuffer,
	COORD dwBufferSize,
	int horizontalLines)
{//записать все в массив и его выводить
	WORD attrib = FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_INTENSITY; //желтый текст на черном фоне
	COORD charPosition = { 0,0 };    // положение курсора после
								  // каждого обновления буфера
	SMALL_RECT writeArea = { 0, 0, dwBufferSize.X, dwBufferSize.Y };
	int tmp = (writeArea.Bottom / horizontalLines) * writeArea.Right;
	char simb = 'X';
	//Создание горизонтальных линий
	for (int i = 0; i < writeArea.Right; i++) {
		for (size_t boxes = 0; boxes < horizontalLines; boxes++)
		{
			consBuffer[i + tmp * boxes].Char.AsciiChar = simb;
			consBuffer[i + tmp * boxes].Attributes = attrib;
		}
	}
	//Создание вертикальных линий
	int tmpForEndHorizont = writeArea.Bottom / horizontalLines;
	for (size_t i = 1; i < writeArea.Bottom - tmpForEndHorizont; i++)
	{
		consBuffer[i * writeArea.Right + writeArea.Right - 1].Char.AsciiChar = simb;
		consBuffer[i * writeArea.Right + writeArea.Right - 1].Attributes = attrib;
		consBuffer[i * writeArea.Right].Char.AsciiChar = simb;
		consBuffer[i * writeArea.Right].Attributes = attrib;
	}
}

void Interface::printString(HANDLE hConsoleOutput, const char title[], COORD startCoord)
{
	int strLength = strlen(title);
	DWORD written;
	WriteConsoleOutputCharacterA(hConsoleOutput, title, strLength, startCoord, &written);
}

void Interface::printArray(HANDLE hConsoleOutput, int* array, COORD startCoord, int col, int length)
{
	int count = startCoord.X;
	DWORD written;
	SetConsoleCursorPosition(hConsoleOutput, startCoord);

	for (size_t i = 0; i < length; i++)
	{
		if (count < (col - 20))
		{
			std::cout << array[i] << ", ";
			if (array[i] < 0)
			{
				count += 4;
				//WriteConsoleOutputCharacterA(hConsoleOutput, array[i] + ", ", 4, startCoord, &written);
			}
			else
			{
				count += 3;
				//WriteConsoleOutputCharacterA(hConsoleOutput, array[i] + ", ", 3, startCoord, &written);
			}
		}
		else
		{
			startCoord.Y += 1;
			SetConsoleCursorPosition(hConsoleOutput, startCoord);
			count = startCoord.X;
		}
	}
}