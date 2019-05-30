#include<iostream>
#include<stack>
using namespace std;
int Partition1(int array[], int left, int right){//时间复杂度O（n）
	int begin = left;
	int end = right;
	int pivot = array[right];
	while (begin < end){
		while (begin < end && array[begin] <= pivot){
			begin++;
		}
		array[end] = array[begin];
		while (begin < end && array[end] >= pivot){
			end--;
		}
		array[begin] = array[end];
	}
	array[begin] = pivot;
	return begin;
}
void Swap(int* p1, int*p2){
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
int Partition2(int array[], int left, int right){//时间复杂度O（n）
	int d = left;
	int i = left;
	while (i < right){
		if (array[i] >=array[right]){
			i++;
		}
		else{
			Swap(array + d, array + i);
			i++;
			d++;
		}
	}
	Swap(array+d, array+right);
	return d;
}
void QuickSort(int array[], int left, int right){//时间复杂度：最好|平均 O（n*log（n）） 最坏 O（n^2）
	if (left >= right){                          // 空间复杂度：O（logn）-O（n）
		return;
	}
	int div = Partition1(array, left, right);
	QuickSort(array, left, div - 1);
	QuickSort(array, div + 1, right);
}
void QuickSortNor(int array[], int left, int right){
	stack<int> s;
	s.push(right);
	s.push(left);
	int _left;
	int _right;
	while (!s.empty()){
		_left = s.top();
		s.pop();
		_right = s.top();
		s.pop();
		if (_left >= _right){
			continue;
		}
		int d = Partition1(array, _left, _right);
		s.push(_right);
		s.push(d + 1);
		s.push(d - 1);
		s.push(_left);
	}
}
int main(){
	int array[10] = { 9, 6, 8, 7, 2, 3, 1, 5, 4, 0 };
	QuickSortNor(array,0,9);
	for (int i = 0; i < 10; i++){
		cout << array[i]<<" ";
	}
	cout << endl;
	system("pause");
	return 0;
}