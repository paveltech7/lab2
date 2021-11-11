#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//10)    В  массиве  А[1..28]  определить  максимальное  значение.Все  элементы, лежащие  до  макси -
//мального, увеличить на первое  значение массива, а все числа, после максимального, рассортировать по убыванию.

using namespace std;

extern "C"
{
	int GetMaxNumPos(int* arr, int length);
	int Increase(int* arr, int max_pos);
	void SortFromMaxToEndUbivanie(int* arr, int length, int max_pos);
}

void printArray(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	srand(time(0));
	const int lenght = 28;
	int C[lenght];
	printf("Random array of 28 integer numbers:\n");
	for (int i = 0; i < lenght; i++)
	{
		int n = rand() % 21 - 10;
		printf("%d ", n);
		C[i] = n;
	}
	int pos_max = GetMaxNumPos(C, lenght);
	printf("\nMax C[%d] = %d\n", pos_max, C[pos_max]);
	printf("-------to max-------\n", Increase(C, pos_max));
	printArray(C, lenght);
	printf("\n-------sort-------\n");
	SortFromMaxToEndUbivanie(C, lenght, pos_max);
	printArray(C, lenght);

	getchar();
	return 0;
}