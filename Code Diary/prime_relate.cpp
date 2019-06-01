#include<iostream>
using namespace std;
bool IsPri(int a)
{
	bool flag = 1;
	for (int i = 2; i<a; i++)
	{
		if (a%i == 0)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

int main()
{
	int n;
	int mini;
	int minj;
	cin >> n;
	int min = n;
	for (int i = 1; i<=n / 2; i++)
	{
		if (IsPri(i) && IsPri(n - i))
		{
			int j = n - i;
			if (j - i <= min)
			{
				min = j - i;
				mini = i;
				minj = j;
			}
		}
	}
	cout << mini << endl;
	cout << minj << endl;
	system("pause");
	return 0;
}