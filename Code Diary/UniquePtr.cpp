#include<iostream>
//unique_ptr(C++11�ṩ)�������������ÿ����͸�ֵ
template<class T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~UniquePtr()
	{
		if (_ptr)
			delete _ptr;
	}
	T& operator*(){ return *_ptr; }

	T* operator->(){
		return _ptr;
	}
private:
	//C++98�������ķ�ʽ��ֻ������ʵ��+������˽��
	UniquePtr(UniquePtr<T> const &);
	UniquePtr & operator=(UniquePtr<T> const &);
	//C++11�������ķ�ʽ��delete
	UniquePtr(UniquePtr<T> const &) = delete;
	UniquePtr & operator=(UniquePtr<T> const &) = delete;
private:
	T* _ptr;
};


//int main()
//{
//	UniquePtr<int> up(new int);
//	//���ܿ���
//	//UniquePtr<int> copy(up);
//	return 0;
//}