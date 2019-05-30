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
		//���ٿռ�
		_start = new T[v.Capacity()];
		//�������ݣ������
		for (size_t i = 0; i < v.Size(); i++)
		{
			_start[i] = v[i];
		}
		//����_finish _endOfStorage
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
		//����size
		++_finish;
	}
	void Reserve(size_t newC)
	{
		//����	��ʱ���ж�ԭ���ռ��Ƿ�Ϊ�գ�Ϊ�ղ���Ҫ���п���
		if (newC > Capacity()){
			T* tmp = new T[newC];
			size_t size = Size();
			if(_start != nullptr)
			{
				//���������T���͵ĸ�ֵ���������������ɿ���
				for (size_t i = 0; i<size; i++)
				{
					tmp[i] = _start[i];
				}
				//���Ϊstring�࣬memcpyֻ������ָ�룬û�п���ָ����ָ������ݣ�(ǳ����)
				//Ȼ��delete�ͷ���ԭ�������ݣ�ָ��û����Ȩ�ޣ��ڶ����ͷŷ���ʱ����
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
			//���ݻᵼ�µ�����ʧЧ���������ݺ�Ҫ���»�ȡ������
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
	//����Eraseɾ��ʱ������������ʧЧ������Խ����ʣ�Ӧ��ÿ�ε��ú��ȡ����������ֵ
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