#include<iostream>
//shared_ptrͨ�����ü�����֧������ָ�����Ŀ���
//RAII��Դ�������ϳ�ʼ��������ָ����ͬ��Դ��ָ��Ҫͨ��������ȡ��
#include<thread>
#include<mutex>

template<class T>
class SharedPtr
{
public:
	//���캯���ڵ�һ��������Դ����
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
			//�������ľ���Դ
			if (--(*_pRefCount) == 0)
			{
				delete _ptr;
				delete _pRefCount;
			}

			//��������¶������Դ�����������ü���
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
		//��������ʹ�ü�1��ԭ�Ӳ���
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
	int* _pRefCount;//���ü���
	T* _ptr;//ָ�������Դ��ָ��
	mutex* _pMutex;//������
};