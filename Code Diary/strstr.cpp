#include<iostream>
using namespace std;
char* strstr(char* dest, char* substr){
	//����ƥ��ʧ�ܻ�ԭsubstr
	char* first = substr;
	while (*dest){
		//���Լ�¼���ص�ַ
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
	//cout<<strstr(s.c_str(), s1.c_str())<<endl;//�Զ�������char*���ͣ�����NULLָ�뵼�±���
	printf("%p",strstr(s.c_str(),s1.c_str()));
	system("pause");
	return 0;
}