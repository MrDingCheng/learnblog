#include<iostream>
using namespace std;
int main(){
		// write code here
	int A, B;
	cin >> A >> B;
	int flag = 1;
		int c = 1;
		int C = 0;
		for (int i = 0; i<32; i++)
		{
			flag = flag << 1;
			if ((((A&c)&(B&c)) == c))
			{
				C = C | (flag);
			}
			else if (((A&c) | (B&c)) == c)
			{
				C = C | c;
			}
			c = c << 1;
		}
		cout<<C<<endl;
		system("pause");
	return 0;
}