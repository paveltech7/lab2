extern "C"
int GetMaxNumPos(int* arr, int length)
{
	int max = arr[0];
	int max_pos = 0;
	for (int i = 0; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			max_pos = i;
		}
	}
	return max_pos;
}
extern "C"
void Increase(int* arr, int max_pos)//Все элементы, лежащие до максимального, увеличить на первое значение массива,
{
	int sum = arr[0];
	for (int i = 0; i < max_pos; i++)
		arr[i] = arr[i] + sum;
}
extern "C"
void SortFromMaxToEndUbivanie(int* arr, int length, int max_pos) //а все числа, после максимального, рассортировать по убыванию.
{
	bool again = true;
	while (again)
	{
		again = false;
		for (int i = max_pos + 1; i < length; i++)
		{
			if (arr[i] < arr[i + 1])
			{
				int tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				again = true;
			}
		}
	}
}