#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;
class String
{
public:
	typedef char* iterator;

	String(char* str = "")
		:_size(strlen(str))
		, _capacity(_size)
		, _str(new char[_size+1])
	{
		strcpy(_str, str);
	}
	void Swap(String &tmp)
	{
		swap(_str, tmp._str);
		swap(_size, tmp._size);
		swap(_capacity, tmp._capacity);
	}
	String(const String& s)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}
	String& operator=(String s)
	{
		Swap(s);
		return *this;
	}
	size_t Size() const
	{
		return _size;
	}
	size_t Capacity() const
	{
		return _capacity;
	}
	char* c_str() const
	{
		return _str;
	}
	//只增容，不减少容量，不改变size
	void Reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			//拷贝原始空间的内容
			strcpy(tmp, _str);
			//释放原有空间
			delete[] _str;
			//指向新的空间
			_str = tmp;
			//更新capacite的值
			_capacity = n;
		}
	}
	//首先检查capacity够不够，如果满了，则扩容
	void PushBack(const char c)
	{
		//if (_size == _capacity)
		//{
		//	//已存满，扩容，检测初始空间是否为0，如果是0，增容为15byte
		//	size_t newC = (_capacity == 0) ? 15 : _capacity * 2;
		//	Reserve(newC);
		//}
		//_str[_size++] = c;
		//_str[_size] = '\0';
		Insert(_size, c);
	}
	void PopBack()
	{
		assert(_size > 0);
		_str[--_size] = '\0';
	}
	//可读可写
	char& operator[](size_t pos)
	{
		assert(pos<_size);
		return _str[pos];
	}
	//只读
	const char& operator[](size_t pos) const
	{
		assert(pos<_size);
		return _str[pos];
	}
	iterator begin()
	{
		return _str;
	}
	iterator end()
	{
		return _str + _size;
	}
	iterator begin() const
	{
		return _str;
	}
	iterator end() const
	{
		return _str + _size;
	}
	void Append(const char* str)
	{
		size_t sz = strlen(str);
		if (sz + _size > _capacity)
		{
			Reserve(_size + sz);
		}
		strcpy(_str + _size, str);
		_size += sz;
		//Insert(_size, str);
	}
	void Resize(size_t n, char c = '\0')
	{
		if (n > _capacity)
		{
			Reserve(n);
		}
		if (_size < n)
		{
			//for (int i = _size; i < n; i++)
			//{
			//	_str[i] = c;
			//}
			memset(_str + _size, c, n - _size);
		}
		_size = n;
		_str[_size] = '\0';
	}
	void Insert(size_t pos, const char c)
	{
		//检查空间是否已满，如果满，增容
		//留出pos位置用于插入字符c，从pos开始的所有字符向后移动一个位置
		//在pos位置插入c
		//更新_size，更新'\0'的位置
		assert(pos<=_size);
		if (_size == _capacity)
		{
			size_t newC = (_capacity == 0) ? 15 : _capacity * 2;
			Reserve(newC);
		}
		for (size_t i = Size(); i > pos - 1; i--)
		{
			_str[i + 1] = _str[i];
		}
		_str[pos] = c;
		_size++;
	}
	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		//检查空间是否足够，不够增容
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			Reserve(_capacity + len);
		}
		//从pos位置开始的数据依次向后挪动
		size_t end = _size + len;
		while (end > pos +len-1)
		{
			_str[end] = _str[end-len];
			end--;
		}
		//从pos位置拷贝str
		memcpy(_str + pos, str, len);
		_size += len;
	}
	void Erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		//pos +len >_size 相当于从pos开始之后的字符都删除了
		if (pos + len >_size)
		{
			_size = pos;
			_str[pos] = '\0';
		}
		else
		{
			//从pos+len位置往后，依次开始向前挪动len个位置
			for (size_t i = pos + len; i <= _size; i++)
			{
				_str[i-len] = _str[i];
			}
			_size -= len;
		}
	}
	String& operator+= (const String& s)
	{
		Append(s._str);
		return *this;
	}
	String& operator+= (const char c)
	{
		PushBack(c);
		return *this;
	}
	String& operator+= (const char* str)
	{
		Append(str);
		return *this;
	}
	size_t find(const char c)
	{
		int i = 0;
		while (i != Size())
		{
			if (_str[i] == c)
				return i;
			i++;
		}
		return -1;
	}
	size_t find(size_t pos,const char* str)
	{
		char *ret = strstr(_str + pos, str);
		if (ret != NULL)
			return ret - _str;
		else
			return -1;
	}
	size_t find(size_t pos, const char c)
	{
		int i = pos;
		while (i != Size())
		{
			if (_str[i] == c)
				return i;
		}
		return -1;
	}
	~String()
	{
		if (_str != nullptr){
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}
	}
	friend ostream& operator<< (ostream& _cout, const String& s);
private:
	//size:有效字符长度，不含'/0'
	//capacity:不含'/0'，比实际大小小1个字节
	size_t _size;
	size_t _capacity;
	char* _str;
};
String operator+(const String&s1, const String& s2)
{
	String tmp(s1);
	tmp += s2;
	return tmp;
}
String operator+(const String&s1, const char* s2)
{
	String tmp(s1);
	tmp += s2;
	return tmp;
}
String operator+(const char* s1, const String& s2)
{
	String tmp(s2);
	tmp.Insert(0, s1);
	return tmp;
}
ostream& operator<< (ostream& _cout, const String& s)
{
	for (auto& e : s)
	{
		_cout << e <<" ";
	}
	return _cout;
}
void PrintStringIterator(const String& s)
{
	String::iterator i = s.begin();
	while (i != s.end()){
		cout << *i << "";
		i++;
	}
	cout << endl;
}
void PrintStringFor(const String& s)
{
	for (auto e : s){
		cout << e <<" ";
	}
	cout << endl;
}
void PrintString(const String& s)
{
	for (size_t i = 0; i < s.Size(); i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;
}
void teststring1()
{
	String s,s1;
	s.PushBack('a');
	s.PushBack('b');
	s.PushBack('c');
	s.Insert(3, 's');//abcs
	cout << s << endl;
	s.Insert(3,"eeee");//abceeees
	cout << s << endl;
	s.Append("defghjkl");
	s1 += 'a';
	s1 += "hello";
	s1 += s;
	cout << s << endl;
	s.Erase(0, 2);
	cout << s << endl;
	s.Resize(26);
	cout << s << endl;
	s.Erase(0,333);
	cout << s << endl;
}
int main()
{
	teststring1();
	system("pause");
	return 0;
}