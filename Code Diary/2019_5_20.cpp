#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
//ɾ����һ���ַ����еĵڶ����ַ��������е������ַ�
int main()
{
	string a;
	string b;
	getline(cin, a);//ֱ��cin�����ַ��������������ַ��пӣ�
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