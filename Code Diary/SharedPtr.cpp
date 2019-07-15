#include<iostream>
//shared_ptr通过引用计数来支持智能指针对象的拷贝
//RAII资源申请马上初始化，后面指向相同资源的指针要通过拷贝获取。
#include<thread>
#include<mutex>

template<class T>
class SharedPtr
{
public:
	//构造函数在第一次申请资源调用
	//SharedPtr<T> sp(new T)
	SharedPtr(T* ptr = nullptr)
		:_ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}

	~SharedPtr(){
		Release();
	}

	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//处理管理的旧资源
			if (--(*_pRefCount) == 0)
			{
				delete _ptr;
				delete _pRefCount;
			}

			//共享管理新对象的资源，并增加引用计数
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			AddRefCount();
		}
		return *this;
	}

	T& operator*(){ return *_ptr; }
	T* operator->(){ return _ptr; }
	int UseCount(){ return *_pRefCount; }
	T* Get(){ return _ptr; }

	void AddRefCount()
	{
		//加锁或者使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
		_pMutex.lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex.unlock();
		if (deleteflag == true)
			delete _pMutex;
	}
	int* _pRefCount;//引用计数
	T* _ptr;//指向管理资源的指针
	mutex* _pMutex;//互斥锁
};