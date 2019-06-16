#include<iostream>
using namespace std;
int DrinkSum(int n, int rem)
{
	int ret = 0;
	if ((n + rem)>2)
	{
		ret = (n + rem) / 3;
		rem = (n + rem) % 3;
		ret += DrinkSum(ret, rem);
	}
	else
		return ret;
	return ret;
}

int main()
{
	int n;
	while (cin >> n)
		cout << DrinkSum(n, 1) << endl;
	system("pause");
	return 0;
}