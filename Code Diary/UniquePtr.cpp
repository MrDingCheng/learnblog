#include<iostream>
//unique_ptr(C++11提供)，防拷贝，不让拷贝和赋值
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
	//C++98防拷贝的方式：只声明不实现+声明成私有
	UniquePtr(UniquePtr<T> const &);
	UniquePtr & operator=(UniquePtr<T> const &);
	//C++11防拷贝的方式：delete
	UniquePtr(UniquePtr<T> const &) = delete;
	UniquePtr & operator=(UniquePtr<T> const &) = delete;
private:
	T* _ptr;
};


//int main()
//{
//	UniquePtr<int> up(new int);
//	//不能拷贝
//	//UniquePtr<int> copy(up);
//	return 0;
//}