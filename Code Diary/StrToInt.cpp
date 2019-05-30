#include<iostream>
#include<string>
using namespace std;
int StrToInt(string str){
	int ret = 0;
	int flag = 1;
	for (char &e : str){
		ret =ret *10 ;
		if ('0' <= e && e <= 9){
			ret += e - '0';
		}
		else if (e == '-' || e == '+'){
			if (e == '-'){
				flag = -1;
			}
		}
	}
	//string::iterator sit = str.begin();
	//while (sit != str.end()){
	//	ret = ret * 10 + (e-)
	//}
	return ret*flag;
}
void reverseString(string& s){
	size_t start = 0;
	size_t end = s.size() - 1;
	while (start < end){
		swap(s[start], s[end]);
		start++;
		end--;
	}
}
int getLastWordLenth(string s){
	int pos = s.rfind(' ');
	return s.size() - pos - 1;
}
int firstUniqChar(string s){
	int hashT[26] = { 0 };
	int i = 0;
	for (;i < s.size(); i++){
		hashT[s[i] - 'a']++;
	}
	for (i = 0; i < s.size(); i++){
		if (hashT[s[i] - 'a'] == 1){
			return i;
		}
	}
	return -1;
}

string addStrings(string num1, string num2) {
	int len1 = num1.size() - 1;
	int len2 = num2.size() - 1;
	int step = 0;
	string ret = "";
	int sum = 0;
	while (len1 >= 0 || len2 >= 0){
		sum = 0;
		sum += step;
		if (len1 >= 0){
			sum += num1[len1]-'0';
		}
		if (len2 >= 0){
			sum += num2[len2] - '0';
		}
		if (sum > 9){
			sum -= 10;
			step = 1;
		}
		else
			step = 0;
		//把当前的值用字符形式保存到字符串中，头插
		ret.insert(0, 1, sum + '0');
		len1--;
		len2--;
	}
	if (step == 1)
		ret.insert(0, 1, '1');
	return ret;
}
string IntToStr(unsigned int a){
	string ret;
	while (a > 9){
		ret += '0' + a % 10;
		a = a / 10;
	}
	ret += a + '0';
	int i = ret.size() - 1;
	int j = 0;
	while (j < i){
		char c = ret[j];
		ret[j] = ret[i];
		ret[i] = c;
		i--;
		j++;
	}
	return ret;
}
unsigned int addStrings1(string num1, string num2) {//不能实现大数字相加
	string::reverse_iterator i = num1.rbegin();
	string::reverse_iterator j = num2.rbegin();
	unsigned int ret = 0;
	int flag = 0;
	while (i != num1.rend()  && j != num2.rend() ){
		ret = ret + (*i + *j - '0' - '0') * pow(10 , flag);
		i++;
		j++;
		flag++;
	}
	if (i == num1.rend() ){
		while (j != num2.rend()){
			ret = ret + (*j - '0') * pow(10, flag);
			j++;
			flag++;
		}
	}
	if (j == num2.rend()){
		while (i != num1.rend()){
			ret = ret + (*i - '0') * pow(10, flag);
			i++;
			flag++;
		}

	}
	return ret;
}
int main(){
	//string s1("sdfffff");
	//int i = firstUniqChar(s1);
	//reverseString(s1);
	//cout << s1<< ' '<<i << endl;
	string s("691");
	string s1("99");
	cout<<addStrings1(s, s1)<<endl;
	system("pause");
	return 0;
}