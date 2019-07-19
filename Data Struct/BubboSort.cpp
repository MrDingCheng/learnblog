#include<iostream>
void Swap(int* p1, int*p2)
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void BubboSort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int flag = 1;
		for (int j = 1; j < size - i; j++)
		{
			if (arr[j - 1]>arr[j])
			{
				Swap(arr + (j - 1), arr + j);
				flag = 0;
			}
		}
		if (flag == 1)
			return;
	}
}

int main()
{
	int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	BubboSort(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}