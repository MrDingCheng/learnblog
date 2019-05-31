#include<iostream>
#include<string>
using namespace std;
int main()
{
	string pPasswordStr;
	while (cin >> pPasswordStr)
	{
		size_t sz = pPasswordStr.size();
		int Num = 0;
		int lchNum = 0;
		int hchNum = 0;
		int nNum = 0;
		int sigNum = 0;
		if (sz <= 4)
		{
			Num = 5;
		}
		else if (sz <= 7)
			Num = 10;
		else if (sz>7)
			Num = 25;
		for (auto e : pPasswordStr)
		{
			if ('0' <= e && e <= '9')
				nNum++;
			else if ('a' <= e && e <= 'z')
				lchNum++;
			else if ('A' <= e && e <= 'Z')
				hchNum++;
			else if (('!' <= e && e <= '/') || (':' <= e && e <= '@') || ('[' <= e && e <= '`') || ('{' <= e && e <= '~'))
				sigNum++;
			else{}
		}
		if (lchNum != 0 && hchNum != 0)
		{
			Num += 20;
		}
		else if ((lchNum == 0 && hchNum != 0) || (lchNum != 0 && hchNum == 0))
			Num += 10;
		if (nNum == 1)
			Num += 10;
		else if (nNum > 1)
			Num += 20;
		if (sigNum == 1)
			Num += 10;
		else if (sigNum > 1)
			Num += 20;
		if (nNum != 0 && lchNum != 0 && hchNum != 0 && sigNum != 0)
			Num += 5;
		else if (nNum != 0 && (lchNum != 0 || hchNum != 0) && sigNum != 0)
			Num += 3;
		else if (nNum != 0 && (lchNum != 0 || hchNum != 0) && sigNum == 0)
			Num += 2;

		if (Num >= 90)
			cout << "VERY_SECURE" << endl;
		else if (Num >= 80)
			cout << "SECURE" << endl;
		else if (Num >= 70)
			cout << "VERY_STRONG" << endl;
		else if (Num >= 60)
			cout << "STRONG" << endl;
		else if (Num >= 50)
			cout << "AVERAGE" << endl;
		else if (Num >= 25)
			cout << "WEAK" << endl;
		else if (Num >= 0)
			cout << "VERY_WEAK" << endl;
	}
	return 0;
}