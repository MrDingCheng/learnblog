#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
#include<string>
using namespace std;
int countLex = 0;
int countLen = 0;
bool LexiComp(string& str1, string& str2)
{
	int ret = str2.compare(str1);
	if (ret > 0)
	{
		countLex++;
		return true;
	}
	return false;
}
bool LenthComp(string& str1, string& str2)
{
	int ret = ((int)str2.length() - (int)str1.length());
	if (ret > 0)
	{
		countLen++;
		return true;
	}
	return false;
}

int main()
{
	int n;
	vector<string> str;
	cin >> n;
	
	for (int i = 0; i<n; i++)
	{
		string s;
		cin>>s;
		str.push_back(s);
	}
	vector<string> str1 = str;
	sort(str.begin(), str.end(), LenthComp);
	sort(str1.begin(), str1.end(), LexiComp);
	if (countLex == 0 && countLen == 0)
		cout << "both" << endl;
	else if (countLex == 0)
		cout << "lexicographically" << endl;
	else if (countLen == 0)
		cout << "lengths" << endl;
	else
		cout << "none" << endl;
	countLex = countLen = 0;
	system("pause");
	return 0;
}