#pragma once
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "Interface.h"
#include "Button.h"

const int col = 80;   // ширина окна консоли ,минимум 50 для вывода текста
const int row = 40;   // высота консоли

const int horizontalLines = 4;//Сколько горизонтальных линий
DWORD fdwSaveOldMode, wdwSaveOldMode;
bool cursorVisible = false;

//10)    В  массиве  А[1..28]  определить  максимальное  значение.Все  элементы, лежащие  до  макси -
//мального, увеличить на первое  значение массива, а все числа, после максимального, рассортировать по убыванию.

//using namespace std;

extern "C"
{
	int GetMaxNumPos(int* arr, int length);
	void Increase(int* arr, int max_pos);
	void SortFromMaxToEndUbivanie(int* arr, int length, int max_pos);
}

int main()
{
	DWORD fdwMode, wdwMode;
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(wHnd, &wdwSaveOldMode);
	GetConsoleMode(rHnd, &fdwSaveOldMode);
	SetConsoleTitle(L"2 lab");

	//-------------------создание массива------------------------------------
	srand(time(0));
	const int lenghtArray = 28;
	int C[lenghtArray];
	for (int i = 0; i < lenghtArray; i++)
	{
		int n = rand() % 10 - 10;
		C[i] = n;
	}
	int pos_max = GetMaxNumPos(C, lenghtArray);
	//-----------------------------------------------------------------------

	fdwMode = ENABLE_MOUSE_INPUT;
	wdwMode = ENABLE_WRAP_AT_EOL_OUTPUT;

	SetConsoleMode(rHnd, fdwMode);
	SetConsoleMode(wHnd, wdwMode);

	// --- 1. Задаем размер консоли и его внутреннего буфера ---
	SMALL_RECT windowSize = { 0,0,col - 1,row - 1 };
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { col,row };   // размеры внутреннего буфера
	// Изменение размера внутреннего буфера окна консоли
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleTextAttribute(wHnd, BACKGROUND_BLUE | BACKGROUND_GREEN |
		BACKGROUND_RED | BACKGROUND_INTENSITY);

	// --- 2. Создаем и заполняем блок данных по размеру консоли
	CHAR_INFO consBuffer[col * row];    // Создание буфера консоли
	for (int i = 0; i < col * row; ++i) {
		// Заполнение буфера консоли пробелами
		consBuffer[i].Char.AsciiChar = ' ';
		consBuffer[i].Attributes =
			BACKGROUND_BLUE | BACKGROUND_GREEN |
			BACKGROUND_RED | BACKGROUND_INTENSITY;
	}
	COORD charPosition = { 0,0 };    // положение курсора после
								  // каждого обновления буфера
	SMALL_RECT writeArea = windowSize;
	// Перенос данных буфера на дисплей
	WriteConsoleOutputA(wHnd, consBuffer, bufferSize,
		charPosition, &writeArea);

	// --- 3. Чтение и анализ буфера ввода. Реакция на события.
	DWORD numEvents = 0;      // Количество непрочитанных сообщений
	DWORD numEventsRead = 0;  // Количество прочитанных сообщений
	bool isRunning = true;    // флаг продолжения работы

	Interface::setInterface(consBuffer, bufferSize, horizontalLines);//рисование интерфейса в окне
	const char strLegendLabel[] = "<Legend>";
	const char strOrigArray[] = "Original array";
	const char strModifArray[] = "Modifided array";
	const char strOrigLabel[] = "<Original array>";
	const char strModifLabel[] = "<Modifided array>";
	const char strExit[] = "Exit";
	const char strLegend1[] = "First window for original array, second window for modifided array. ";
	const char strLegend2[] = "Button <Exit> for close program";
	const char strLegend3[] = "Create Pavel Lommonosov";
	int xStartDrawBox = (col - (strlen(strOrigArray) + strlen(strModifArray) + strlen(strExit) + 2)) / 2;
	int yStartDrawBox = (row / horizontalLines) * (horizontalLines - 1) + (row / horizontalLines / 2) - 1;

	COORD StartDrawBox1 = { xStartDrawBox , yStartDrawBox };
	Button boxOrig(consBuffer, StartDrawBox1, strOrigArray, bufferSize);
	StartDrawBox1 = { (SHORT)(StartDrawBox1.X + strlen(strOrigArray) + 1), (SHORT)yStartDrawBox };
	Button boxModif(consBuffer, StartDrawBox1, strModifArray, bufferSize);
	StartDrawBox1 = { (SHORT)(StartDrawBox1.X + strlen(strModifArray) + 1), (SHORT)yStartDrawBox };
	Button boxExit(consBuffer, StartDrawBox1, strExit, bufferSize);

	WriteConsoleOutputA(wHnd, consBuffer, bufferSize,
		charPosition, &writeArea);

	Interface::printString(wHnd, strLegend1, { 2,2 });
	Interface::printString(wHnd, strLegend2, { 2,3 });
	Interface::printString(wHnd, strLegend3, { 2,4 });
	Interface::printString(wHnd, strLegendLabel, { (SHORT)(col / 2 - strlen(strLegendLabel) / 2), 0 });
	Interface::printString(wHnd, strOrigLabel, { (SHORT)(col / 2 - strlen(strOrigLabel) / 2) ,  (row / horizontalLines) * 1 });
	Interface::printString(wHnd, strModifLabel, { (SHORT)(col / 2 - strlen(strModifLabel) / 2) , (row / horizontalLines) * 2 });
	//отключение видимости курсора
	CONSOLE_CURSOR_INFO ccInfo;
	ccInfo.bVisible = cursorVisible;
	ccInfo.dwSize = 20;
	SetConsoleCursorInfo(wHnd, &ccInfo);

	//Если isRunning=false, то программа завершается
	while (isRunning) {
		// Определить количество событий, связанных с консолью
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			// выделение памяти для хранения данных о событиях
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			// Извлечение данных во временный буфер событий и
			// определение количества событий numEventsRead
			ReadConsoleInput(rHnd, eventBuffer,
				numEvents, &numEventsRead);

			// Цикл по всем извлеченным событиям
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT) {
					// анализ виртуальных кодов клавиш
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_ESCAPE:
						isRunning = false;
						break;
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					COORD COORDClick = { eventBuffer[i].Event.MouseEvent.dwMousePosition.X ,eventBuffer[i].Event.MouseEvent.dwMousePosition.Y };
					// вычисление индекса в текстовом буфере консоли
					int consBuffPos =
						eventBuffer[i].Event.MouseEvent.dwMousePosition.X +
						col * eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState &
						FROM_LEFT_1ST_BUTTON_PRESSED) {
						if (boxOrig.checkClick(COORDClick))
						{
							Interface::printArray(wHnd, C, { 2, (row / horizontalLines) * 1 + 2 }, col, lenghtArray);
						}
						else if (boxModif.checkClick(COORDClick))
						{
							Increase(C, pos_max);
							SortFromMaxToEndUbivanie(C, lenghtArray, pos_max);
							Interface::printArray(wHnd, C, { 2, (row / horizontalLines) * 2 + 2 }, col, lenghtArray);
						}
						else if (boxExit.checkClick(COORDClick))
						{
							isRunning = false;
							break;
						}
					}
				}
			}
			delete[] eventBuffer;  // освобождение памяти
		}
	}
	// Restore input mode on exit.
	SetConsoleMode(rHnd, fdwSaveOldMode);
	SetConsoleMode(wHnd, wdwSaveOldMode);
	return 0;
}