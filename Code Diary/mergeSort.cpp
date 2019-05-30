#include<iostream>
using namespace std;
void Merge(int array[], int left, int mid, int right,int *extra){//合并两个有序数组 array[left,mid);array[mid,right)
	int size = right - left;
	int left_index = left;
	int right_index = mid;
	int extra_index = left;
	while (left_index < mid && right_index < right){
		if (array[left_index] <= array[right_index]){
			extra[extra_index] = array[left_index];
			left_index++;
		}
		else{
			extra[extra_index] = array[right_index];
			right_index++;
		}
		extra_index++;
	}
	while (left_index < mid){
		extra[extra_index] = array[left_index];
		left_index++;
		extra_index++;
	}
	while (right_index < right){
		extra[extra_index] = array[right_index];
		right_index++;
		extra_index++;
	}
	for (int i = left; i < left + size; i++){
		array[i] = extra[i];
	}
}
void MergeSort(int array[], int left, int right, int* extra){
	if (left >= right){
		return;
	}
	if (right == left + 1){
		return;
	}
	int mid = left + (right - left) / 2;
	MergeSort(array, left, mid,extra);
	MergeSort(array, mid, right,extra);
	Merge(array, left, mid, right,extra);
}
int main(){
	int array[10] = { 0, 4, 7, 8, 5, 2, 4, 6, 9, 1 };
	int size = sizeof(array) / sizeof(int);
	int *extra = (int*)malloc(sizeof(int)*size);
	MergeSort(array, 0, size,extra);
	free(extra);
	for (int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	system("pause");
	return 0;
}