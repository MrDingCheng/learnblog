#include<iostream>
#include<fstream>
using namespace std;
struct Info
{
	char ip[20];
	int port;
};
class Config
{
public:
	Config(string filename)
		:_filename(filename)
	{}
	//�ֽ�����д�����ڴ���ʽ��д��
	void ReadBin(Info& info)
	{
		ifstream fin(_filename.c_str());
		fin.read((char*)&info, sizeof(info));
		//seekg:�����ļ�ָ���λ��
		fin.seekg(0,ifstream::end); 
		//tellg:�ļ�ָ��������ļ���ʼλ�õ�ƫ����
		size_t byteNum=fin.tellg();
		cout << "byteNum:" << byteNum << endl;
		fin.close();
		cout << info.ip << endl;
		cout << info.port << endl;
	}
	void WriteBin(Info& info)
	{
		ofstream fout(_filename.c_str());
		//fout.seekp(0, ofstream::end);
		//fout.tellp;
		fout.write((char*)&info, sizeof(info));
		fout.close();
	}
	//�ַ�����д
	void ReadText(Info& info)
	{
		ifstream fin(_filename.c_str());
		fin >> info.ip;
		fin >> info.port;
		fin.close();
	}
	void WriteText(Info& info)
	{
		ofstream fout(_filename.c_str());
		fout << info.ip << endl;
		fout << info.port << endl;
		fout.close();
	}
	
private:
	string _filename;
};
int main()
{
	Info info;
	Info ReadInfo;
	strcpy_s(info.ip,"www.baidu.com");
	info.port = 80;
	Config cfg("Config.txt");
	cfg.WriteBin(info);
	cfg.ReadBin(ReadInfo);
	cfg.WriteText(info);
	cfg.ReadText(ReadInfo);
	system("pause");
	return 0;
}