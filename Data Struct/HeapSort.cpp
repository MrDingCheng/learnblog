#include<iostream>
using namespace std;
//堆排序

void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//排升序建大堆(向下调整)
void AdjustDown(int arr[], int size,int root)
{
	//判断root是不是叶子
	int i = 2 * root + 1;

	if (i >= size){
		return;
	}

	//找到大孩子，考虑有没有右孩子
	int max = i;
	if (i + 1 < size && arr[i + 1] > arr[i]){
		max = i + 1;
	}

	//大孩子的值与根的值比较
	if (arr[root] >= arr[max]){
		return;
	}
	//交换
	Swap(arr + root, arr + max);

	//继续对max调整
	AdjustDown(arr, size, max);

}
void HeapSort(int arr[], int size)
{
	for (int i = (size - 1 - 1) / 2; i >= 0;i--)
		AdjustDown(arr,size,i);
	for (int i = 0; i < size; i++){
		Swap(&arr[0], arr + size - 1 - i);
		//向下调整，把堆结构调整为正确状态
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