#include<iostream>
using namespace std;
//��������
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int k = arr[i];
		//�ҵ�arr[i]�Ĳ���λ��
		int j = i - 1;
		for (; j >= 0; j--)
		{
			if (arr[j] > k)//����arr[i]��������ƶ�
			{
				arr[j + 1] = arr[j];
			}
			else
				break;
		}
		arr[j+1] = k;
	}
}
//ϣ������
void InsertSortWithGap(int arr[], int size, int gap)
{
	for (int i = gap; i < size; i++)
	{
		int k = arr[i];
		//�ҵ�arr[i]�Ĳ���λ��
		int j = i - gap;
		for (; j >= 0; j -= gap)
		{
			if (arr[j] > k)//����arr[i]��������ƶ�
			{
				arr[j + gap] = arr[j];
			}
			else
				break;
		}
		arr[j + gap] = k;
	}
}
void ShellSort(int array[], int size)
{
	int gap = size;
	while (1){
		gap = gap / 3 + 1;
		InsertSortWithGap(array, size, gap);
		if (gap == 1)
			break;
	}
	
}
int main()
{
	int array[] = { 9, 3, 2, 1, 5, 6, 7, 8, 0 };
	int size = sizeof(array) / sizeof(array[0]);
	//InsertSort(array, size);
	ShellSort(array, size);
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}