#include<iostream>
using namespace std;

void Merge(int array[], int left, int mid, int right, int tmp[]){
	int i = left;
	int j = mid+1;
	int k = left;
	while (i <= mid && j <= right){
		if (array[i] < array[j]){
			tmp[k++] = array[i++];
		}
		else{
			tmp[k++] = array[j++];
		}
	}
	while (i <= mid){
		tmp[k++] = array[i++];
	}
	while (j <= right){
		tmp[k++] = array[j++];
	}
	for (int l = left; l <= right; l++){
		array[l] = tmp[l];
	}
}

void MergeSort(int array[], int left, int right, int tmp[]){//[left,right]
	if (left >= right){
		return;
	}
	int mid = left + (right - left)/2;
	MergeSort(array, left, mid,tmp);
	MergeSort(array, mid+1, right,tmp);//划分
	Merge(array, left, mid, right, tmp);//合并
}

int main(){
	int array[] = { 5, 1, 2, 4, 3, 7, 6, 8, 9, 0 };
	int tmp[10];
	MergeSort(array, 0, 9, tmp);
	for (int i = 0; i < 10; i++){
		cout << array[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}