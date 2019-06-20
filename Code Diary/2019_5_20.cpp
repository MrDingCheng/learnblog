#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
//删除第一个字符串中的第二个字符串所含有的所有字符
int main()
{
	string a;
	string b;
	getline(cin, a);//直接cin输入字符串，遇到换行字符有坑！
	getline(cin, b);
	string::iterator j = a.begin();
	string::iterator i = b.begin();
	while (i != b.end())
	{
		j = a.begin();
		while (j != a.end() && i != b.end())
		{
			if (*i == *j)
			{
				a.erase(j);
			}
			else
			{
				j++;
			}
		}
		i++;
	}
	cout << a << endl;
	system("pause");
	return 0;
}