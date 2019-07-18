#include "MD5.h"


MD5::MD5()
{
	init();

	memset(_chunk, 0, _chunkByte);
	_lastByte = _totalByte = 0;
}
std::string MD5::getFileMd5(const char* filename)
{
	std::ifstream fin(filename, std::ifstream::binary);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin.read((char*)_chunk,_chunkByte);
			if (_chunkByte != fin.gcount())
				break;
			_totalByte += _chunkByte;
			calculateMD5((size_t*)_chunk);
		}
		_lastByte = fin.gcount();
		_totalByte += _lastByte;
		calculateMD5Final();
	}
	return ChangeHex(_a) + ChangeHex(_b) + ChangeHex(_c) + ChangeHex(_d);
}

std::string MD5::getStringMd5(const std::string str)
{
	if (str.empty())
		return "";
	unsigned char* pstr = (unsigned char*)str.c_str();
	size_t numChunk = str.size() / _chunkByte;
	for (size_t i = 0; i < numChunk; ++i)
	{
		_totalByte += _chunkByte;
		calculateMD5((size_t*)pstr + i*_chunkByte);
	}
	_lastByte = str.size() % _chunkByte;
	memcpy(_chunk, pstr + _totalByte, _lastByte);
	_totalByte += _lastByte;
	calculateMD5Final();
	return ChangeHex(_a) + ChangeHex(_b) + ChangeHex(_c) + ChangeHex(_d);
}
//0x23456789 ->89674523
std::string MD5::ChangeHex(size_t num)
{
	static std::string strMap = "0123456789abcdef";
	std::string ret;
	std::string byteStr;
	for (size_t i = 0; i < 4; i++)
	{
		byteStr = "";
		size_t b = (num >> (i * 8)) & 0xff;
		for (size_t j = 0; j < 2; j++)
		{
			byteStr.insert(0, 1, strMap[b % 16]);
			b /= 16;
		}
		ret += byteStr;
	}
	return ret;
}
void MD5::init()
{
	//初始化_a,_b,_c,_d
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;

	size_t _sft[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7,
		12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6,
		10, 15, 21, 6, 10, 15, 21 };
	//_k[i] 2^(32) * abs(sin(i))
	for (int i = 0; i < 64; i++) { 
		_k[i] = (size_t)(abs(sin(i + 1)) * pow(2, 32));
	}
}
void MD5::calculateMD5(size_t* chunk)
{
	size_t a = _a;
	size_t b = _b;
	size_t c = _c;
	size_t d = _d;
	//chunk[g] f:哈希函数的返回值
	size_t f, g;
	//64次变换，分为4轮操作，每轮操作16个子操作
	for (size_t i = 0; i < 64; ++i)
	{
		if (0 <= i && i < 16)
		{
			f = F(b, c, d);
			g = i;
		}
		else if (16 <= i && i < 32)
		{
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i && i < 48)
		{
			f = H(b, c, d);
			g = (3 * i + 1) % 16;

		}
		else
		{
			f = I(b, c, d);
			g = (7 * i + 1) % 16;

		}
		a = d;
		d = c;
		c = b;
		b = b + ShiftLeftRotate(a + f + _k[i] + chunk[g], _sft[i]);
	}//64次变换完毕
	_a += a;
	_b += b;
	_c += c;
	_d += d;
}

void MD5::calculateMD5Final()
{
	//_lastByte:<64byte,表示最后一块数据的大小
	unsigned char* p = _chunk + _lastByte;
	//填充位的前八bit位:1000 0000 即0x80
	*p++ = 0x80;
	size_t remainFillByte = _chunkByte - _lastByte - 1;
	if (remainFillByte < 8)//剩余空间放不下8字节的原数据的位长度
	{
		memset(p, 0, remainFillByte);
		calculateMD5((size_t*)_chunk);
		memset(_chunk, 0, _chunkByte);
	}
	else
	{
		memset(p, 0, remainFillByte);
	}
	//最后的64bit存放原始文档的bit长度
	((unsigned long long*)_chunk)[7] = _totalByte * 8;
	calculateMD5((size_t*)_chunk);
}
