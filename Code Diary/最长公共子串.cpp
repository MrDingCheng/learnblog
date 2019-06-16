#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main()
{
	string str1, str2;
	cin >> str1;
	cin >> str2;
	int max = 0;
	auto ret = str1.begin();
	for (auto i = str1.begin(); i != str1.end();){
		for (auto j = str2.begin(); j != str2.end();){
			int count = 0;
			auto tmp = i;
			while (i!=str1.end() && j != str2.end() && *i==*j){
				i++;
				j++;
				count++;
			}
			if (count>max)
			{
				ret = tmp;
				max = count;
			}
			if (j != str2.end())
				j++;
		}
		if (i != str1.end())
			i++;
	}
	for (int i = 0; i<max; i++){
		printf("%c", *(ret + i));
	}
	cout << endl;
	system("pause");
	return 0;
}