#include<iostream>
using namespace std;
void Swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Partion1(int array[], int left, int right){
	int key = array[right - 1];
	int begin = left;
	int end = right-1;
	while (begin<end){
		while (begin<end && array[begin]<=key){
			begin++;
		}
		while (begin<end && array[end]>=key){
			end--;
		}
		if (begin<end)
			Swap(array+begin, array+end);
	}
	Swap(array + begin, array + (right - 1));
	return begin;
}

int Partion2(int array[], int left, int right){
	int key = array[right - 1];
	int begin = left;
	int end = right-1;
	while (begin<end){
		while (begin < end && array[begin] <= key){
			begin++;
		}
		if (begin < end){
			array[end] = array[begin];
			end--;
		}
		while (begin<end && array[end] >= key){
			end--;
		}
		if (begin<end){
			array[begin] = array[end];
			begin++;
		}
	}
	array[begin] = key;
	return begin;
}

int Partion3(int array[], int left, int right){
	int cur = left;
	int pre = cur-1;
	int key = array[right - 1];
	while (cur<right){
		if (array[cur]<key && ++pre != cur){
			Swap(array + cur, array + pre);
		}
		cur++;
	}
	if (++pre != right - 1)
		Swap(array + pre, array + (right - 1));
	return pre;
}
void QuickSort(int array[], int left, int right){
	if (right - left > 1){
		int div = Partion3(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}
void Test(){
	int array[] = { 9, 1, 3, 2, 5, 4, 6, 7, 8 };
	QuickSort(array, 0, (sizeof(array) / sizeof(array[0])));
}
int main(){
	Test();
	return 0;
}