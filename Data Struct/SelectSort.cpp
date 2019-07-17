#include<iostream>
using namespace std;
void SelectSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i]>arr[j])
			{
				int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}

int main()
{
	int array[] = { 0, 2, 1, 4, 3, 6, 5, 8, 7, 2 };
	int size = sizeof(array) / sizeof(array[0]);
	SelectSort(array, size);
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";

	}
	cout << endl;
	system("pause");
	return 0;
}