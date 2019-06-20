#include<iostream>
using namespace std;


int way(int i, int j)
{
	if (i == 0 || j == 0)
	{
		return 1;
	}
	return way(i - 1, j) + way(i, j - 1);
}
int main()
{
	int n, m;
	cin >> n >> m;
	cout << way(n, m) << endl;
	system("pause");
	return 0;
}