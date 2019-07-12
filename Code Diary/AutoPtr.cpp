//auto_ptr(C++98���)�����󿽱����߸�ֵ��ǰ��Ķ����������
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

	//һ�������������ͽ�ap����Դת�Ƶ���ǰ�����У�Ȼ����ap������������Դ�Ͽ���ϵ
	//�����ͽ����һ��ռ䱻�������ʹ�ö���ɳ����������
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		//����Ƿ�Ϊ�Լ����Լ���ֵ
		if (this != &ap)
		{
			//�ͷŵ�ǰ��������Դ
			if (_ptr)
				delete _ptr;

			//ת��ap����Դ����ǰ������
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
//	//ap�����գ������ó���
//	//ap->_year = 2018;
//	system("pause");
//	return 0;
//}