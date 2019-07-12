//auto_ptr(C++98设计)当对象拷贝或者赋值后，前面的对象就悬空了
#include<iostream>
template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}

	//一旦发生拷贝，就将ap中资源转移到当前对象中，然后令ap与其所管理资源断开联系
	//这样就解决了一块空间被多个对象使用而造成程序崩溃问题
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		//检查是否为自己给自己赋值
		if (this != &ap)
		{
			//释放当前对象中资源
			if (_ptr)
				delete _ptr;

			//转移ap中资源到当前对象中
			_ptr = ap._ptr;
			ap._ptr = nullptr;
		}
		return *this;
	}

	T& operator*(){ return *_ptr; }

	T* operator->(){ return _ptr; }
private:
	T* _ptr;
private:

};
struct Date
{
	int _year=2019;
	int _month=1;
	int _day=1;
};
//int main()
//{
//	AutoPtr<Date> ap(new Date);
//
//	AutoPtr<Date> copy(ap);
//	//ap被悬空，解引用出错
//	//ap->_year = 2018;
//	system("pause");
//	return 0;
//}