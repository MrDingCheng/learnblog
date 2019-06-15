#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<vector<int>> v1,v2;

	int T;
	cin >> T;
	v1.resize(T);
	v2.resize(T);
	int n, k;
	int i = 0;
	for (; i < T;i++){
		cin >> n;
		cin >> k;
		int t = 2 * n;
		while (t--)
		{
			int x;
			cin >> x;
			v1[i].push_back(x);
		}
		for (int j = 1; j <= k; j++){
			if (j == 1)
			{
				auto begin = v1[i].begin();
				auto begin2 = v1[i].begin() + n;
				while (begin2 != v1[i].end())
				{
					v2[i].push_back(*begin);
					begin++;
					v2[i].push_back(*begin2);
					begin2++;
				}
			}
			else{
				vector<int> v3(v2[i].begin(), v2[i].end());
				auto begin = v3.begin();
				auto begin2 = v3.begin() + n;
				int j = 0;
				while (j < 2 * n - 1)
				{
					v2[i][j] = *begin;
					begin++;
					v2[i][j + 1] = *begin2;
					begin2++;
					j += 2;
				}
			}
		}
	}
	for (int i = 0; i < v2.size(); i++){
		for (auto e : v2[i])
			cout << e << " ";
	}
	cout << endl;
	return 0;
}
