#include<iostream>
#include<string>
using namespace std;
string AddLongInteger(string& addend, string& augend)
{
	string ret;
	auto i = addend.rbegin();
	auto j = augend.rbegin();

	while (i != addend.rend() && j != augend.rend()){
		ret.push_back(*i / 2 + *j / 2);
		i++;
		j++;
	}
	while (i != addend.rend())
		ret.push_back(*i);
	while (j != augend.rend())
		ret.push_back(*j);
	return ret;
}

int main()
{
	string str1, str2, ret;
	getline(cin, str1);
	getline(cin, str2);
	ret = AddLongInteger(str1, str2);
	for (auto k = ret.rbegin(); k != ret.rend(); k++)
		cout << *k;
	cout << endl;
	system("pause");
	return 0;
}