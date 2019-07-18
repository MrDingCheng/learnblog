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
	//计算MD5值（除最后一块）
	void calculateMD5(size_t* chunk);
	//计算最后一块填充后的MD5值
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

	size_t _k[N];//存放k[i]
	size_t _sft[N];// 存放_sft[i]
	const size_t _chunkByte = 64;//每一块数据的字节大小
	unsigned char _chunk[N];

	size_t _lastByte;//最后一块数据的未填充字节大小
	unsigned long long int _totalByte;//原始文档的字节长度
};