#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
template<class T>
class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}
	Vector(const Vector<T>& v)
	{
		//开辟空间
		_start = new T[v.Capacity()];
		//拷贝内容（深拷贝）
		for (size_t i = 0; i < v.Size(); i++)
		{
			_start[i] = v[i];
		}
		//更新_finish _endOfStorage
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Capacity();
	}

	size_t Size() const
	{
		return _finish - _start;
	}
	size_t Capacity() const
	{
		return _endOfStorage - _start;
	}
	void Push_back(const T& val)
	{
		if (_finish == _endOfStorage)
		{
			size_t newC = (_start == nullptr ? 1 : 2 * Capacity());
			Reserve(newC);
		}
		*_finish = val;
		//更新size
		++_finish;
	}
	void Reserve(size_t newC)
	{
		//拷贝	的时候判断原来空间是否为空，为空不需要进行拷贝
		if (newC > Capacity()){
			T* tmp = new T[newC];
			size_t size = Size();
			if(_start != nullptr)
			{
				//深拷贝，调用T类型的赋值运算符重载依次完成拷贝
				for (size_t i = 0; i<size; i++)
				{
					tmp[i] = _start[i];
				}
				//如果为string类，memcpy只拷贝了指针，没有拷贝指针所指向的内容，(浅拷贝)
				//然后delete释放了原来的内容，指针没访问权限，第二次释放访问时出错
				//memcpy(tmp,_start,sizeof(T)*size);
				delete []_start;
			}
			_start = tmp;
			_finish = _start + size;
			_endOfStorage = _start + newC;
		}
	}
	T& operator[](size_t pos)
	{
		assert(pos < Size());
		return _start[pos];
	}
	const T& operator[](size_t pos) const
	{
		assert(pos < Size());
		return _start[pos];
	}
	iterator begin()
	{
		return _start;
	}
	iterator end()
	{
		return _finish;
	}
	const_iterator begin() const
	{
		return _start;
	}
	const_iterator end() const
	{
		return _finish;
	}
	iterator Insert(iterator pos, const T& val)
	{
		assert(pos >= _start && pos <= _finish);
		size_t len = pos - _start;
		if (_finish == _endOfStorage)
		{
			size_t size = Size();
			size_t newC = (_start == nullptr ? 1 : 2 * Capacity());
			Reserve(newC);
			//增容会导致迭代器失效，所以增容后要重新获取迭代器
			pos = _start + size;
		}
		iterator end = _finish - 1;
		while (end >= pos)
		{
			*(end + 1) = *end;
			--end;
		}
		*pos = val;
		++_finish;
		return pos;
	}
	//调用Erase删除时，迭代器可能失效，导致越界访问，应在每次调用后获取迭代器返回值
	iterator Erase(iterator pos)
	{
		assert(pos < _finish && pos >= _start);
		iterator begin = pos + 1;
		while (begin < _finish)
		{
			*(begin - 1) = *begin;
			begin++;
		}
		--finish;
		return pos;
	}
	void Resize(size_t n,const T& val = T())
	{
		if (n <= Size())
		{
			_finish = _start + n;
		}
		else
		{
			if (n > Capacity())
			{
				Reserve(n);
			}
			while (_finish != _start + n)
			{
				*_finish = val;
				_finish++;
			}
		}
	}
	~Vector()
	{
		if (_start != nullptr)
			delete[] _start;
		_start = nullptr;
		_finish = nullptr;
		_endOfStorage = nullptr;
	}
private:
	T* _start;
	T* _finish;
	T* _endOfStorage;
};
template<class T>
void PrintVector(const Vector<T> v)
{
	for (size_t i = 0; i < v.Size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}
template<class T>
void PrintVectorFor(const Vector<T> v)
{
	for (auto e : v)
	{
		cout << e << "";
	}
	cout << endl;
}
void Test()
{
	Vector<string> v1;
	v1.Push_back("abc");
	PrintVector(v1);
}
int main()
{
	Test();
	system("pause");
	return 0;
}