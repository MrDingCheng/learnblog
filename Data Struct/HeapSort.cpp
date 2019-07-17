#include<iostream>
using namespace std;
//������

void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//�����򽨴��(���µ���)
void AdjustDown(int arr[], int size,int root)
{
	//�ж�root�ǲ���Ҷ��
	int i = 2 * root + 1;

	if (i >= size){
		return;
	}

	//�ҵ����ӣ�������û���Һ���
	int max = i;
	if (i + 1 < size && arr[i + 1] > arr[i]){
		max = i + 1;
	}

	//���ӵ�ֵ�����ֵ�Ƚ�
	if (arr[root] >= arr[max]){
		return;
	}
	//����
	Swap(arr + root, arr + max);

	//������max����
	AdjustDown(arr, size, max);

}
void HeapSort(int arr[], int size)
{
	for (int i = (size - 1 - 1) / 2; i >= 0;i--)
		AdjustDown(arr,size,i);
	for (int i = 0; i < size; i++){
		Swap(&arr[0], arr + size - 1 - i);
		//���µ������Ѷѽṹ����Ϊ��ȷ״̬
		AdjustDown(arr, size-1-i, 0);
	}
}

int main()
{
	int array[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int size = sizeof(array) / sizeof(array[0]);
	HeapSort(array, size);
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;

}