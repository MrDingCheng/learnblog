#include<iostream>
using namespace std;
char* strstr(char* dest, char* substr){
	//用以匹配失败还原substr
	char* first = substr;
	while (*dest){
		//用以记录返回地址
		char* ret = dest;
		substr = first;
		while (*dest == *substr && *dest && *substr){
			dest++;
			substr++;
		}
		if (*substr == '\0'){
			return ret;
		}
		dest++;
	}
	return nullptr;
}
int main()
{
	string s("abc");
	string s1("abc");
	//cout<<strstr(s.c_str(), s1.c_str())<<endl;//自动解引用char*类型，返回NULL指针导致崩溃
	printf("%p",strstr(s.c_str(),s1.c_str()));
	system("pause");
	return 0;
}