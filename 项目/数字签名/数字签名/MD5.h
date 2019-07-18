#pragma once
#include<memory>
#include <math.h>
#include <fstream>
#include<string>
#define N 64


class MD5
{
public:
	MD5();
	std::string getFileMd5(const char* filename);
	std::string getStringMd5(const std::string str);

private:

	void init();
	size_t ShiftLeftRotate(size_t num, size_t n)
	{
		return (num << n) | (num >> (32- n));
	}
	//����MD5ֵ�������һ�飩
	void calculateMD5(size_t* chunk);
	//�������һ�������MD5ֵ
	void calculateMD5Final();

	std::string ChangeHex(size_t num);

	size_t F(size_t x, size_t y, size_t z)
	{
		return (x&y) | ((~x) & z);
	}
	size_t G(size_t x, size_t y, size_t z)
	{
		return  (x & z) | (y & (~z));
	}
	size_t H(size_t x, size_t y, size_t z)
	{
		return  x ^ y ^ z;
	}
	size_t I(size_t x, size_t y, size_t z)
	{
		return  y ^ (x | (~z));
	}
private:
	size_t _a;
	size_t _b;
	size_t _c;
	size_t _d;

	size_t _k[N];//���k[i]
	size_t _sft[N];// ���_sft[i]
	const size_t _chunkByte = 64;//ÿһ�����ݵ��ֽڴ�С
	unsigned char _chunk[N];

	size_t _lastByte;//���һ�����ݵ�δ����ֽڴ�С
	unsigned long long int _totalByte;//ԭʼ�ĵ����ֽڳ���
};