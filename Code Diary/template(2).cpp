#include<iostream>
using namespace std;
////����ģ�����
//template<class T1, typename T2>
//T1 Add(const T1& a, const T2& b)
//{
//	return a + b;
//}
////������ģ��������ɵ���һ������ʹ��
//template<class T,size_t N>
//class Array
//{
//	T a[N];
//};
//int main()
//{
//	Array<int, 10> arr1;
//	Array<double, 100> arr2;
//	return 0;
//}
//template<class T>
//bool isEqual(T& a, T& b)
//{
//	return a == b;
//}
////const ���δ�λ��const ���ε�a,b
//template<class T>
//bool isGreater(const T& a,const T& b)
//{
//	return a > b;
//}
////1.��Ҫ��һ���Ѿ����ڵ�ͨ��ģ�庯��
////2.ģ�����Ϊ��
////3.��������Ҫ��ʽд��Ҫ�ػ�������
////4.�ػ������͵ĸ�ʽҪ��ͨ�õ�ģ�������ʽһ��
////5.һ�㲻ȥд����ģ����ػ��汾������ģ����ػ��Ƚϸ��ӣ��ᱨ��һЩ��ֵĴ���
//// ������ں���ģ�崦���˻��߱���ģ�ȥʵ��һ�ݶ�Ӧ���͵���ͨ����
//template<>
//bool isGreater<char*&>(char*& const a,char*& const b)
//{
//	if (strcmp(a, b) > 0)
//		return true;
//	return false;
//}
//bool isGreater(char* a, char* b)
//{
//	if (strcmp(a, b) > 0)
//		return true;
//	return false;
//}
//int main()
//{
//	int a = 10, b = 20;
//	char str1[] = "hello";
//	char str2[] = "world";
//	cout << isEqual(a, b)<<endl;
//	cout << isEqual(str1, str2) << endl;//bool isEquai(char*& a,char*& b)
//	cout << isGreater(a, b)<<endl;
//	cout << isGreater(&str1, &str2) << endl;
//
//	system("pause");
//	return 0;
//}
//��ģ���ػ�
//		1.ȫ�ػ�
//		2.���ػ�
//template<class T1, class T2>
//class Data
//{
//public:
//	Data() { cout << "Data<T1, T2>" << endl; }
//private:
//	T1 _d1;
//	T2 _d2;
//};
////ȫ�ػ�
//template<>
//class Data<int, char>
//{
//public:
//	Data() { cout << "Data<int, char>" << endl; }
//private:
//	int _d1;
//	char _d2;
//};
////���ػ�
////1.�����ػ�
//template<class T>
//class Data<T, char>
//{
//public:
//	Data() { cout << "Data<T, char>" << endl; }
//private:
//	T _d1;
//	char _d2;
//};
////���ػ�
////2.��ģ���������һ������
//template<class T1,class T2>
//class Data<T1*,T2*>
//{
//public:
//	Data() { cout << "Data<T1*, T2*>" << endl; }
//private:
//	T1* _d1;
//	T2* _d2;
//};
//template<class T1, class T2>
//class Data<T1&, T2&>
//{
//public:
//	Data() { cout << "Data<T1&, T2&>" << endl; }
//private:
//	T1 _d1;
//	T2 _d2;
//};
//int main()
//{
//	Data<int, int> d1;  //Data<T1,T2>
//	Data<int, char> d2; //Data<int, char>
//	Data<char, char> d3;// Data<T, char>
//	Data<int*, int*> d4;//Data<T*,T*>
//	Data<int&, int&> d5;//Data<T&,T&>
//	system("pause");
//	return 0;
//}

//�������ݣ� ����
//memcpy: һƬ�ڴ濽����Ч�ʸ� ��O(1)
//��ֵ����=��ÿ��Ԫ�����ο�����Ч�ʽϵ�: O(n)
//STL��������·��
//		1.�������ͣ�memcpy
//		2.�Զ������ͣ���ֵ����
//POD:Plain Old Data-->��������

//RTTI :Run Time Type Information/Identification
//RTTI :typeid(a).name() ����ʱ����ʶ��
//���� isPODType(const char* tp):ȱ�ݣ�Ч�ʽϵͣ�ʱ�临�Ӷ�ΪO(n^2)
//bool isPODType(const char* tp)
//{
//	static char* typeArr[] = { "char", "short", "int", "long", "long long", "float",
//		"double", "long double" };
//	for (int i = 0; i < sizeof(typeArr) / sizeof(typeArr[0]); i++)
//	{
//		if (0 == strcmp(tp, typeArr[i]))
//			return true;
//	}
//	return false;
//}
//template<class T>
//void Copy(T* dst, const T* src, size_t sz, bool isPODtyde)
//{
//	if (isPODtyde(typeid(T).name()))
//	{
//		memcpy(dst, src, sizeof(T)*sz);
//	}
//	else
//	{
//		for (int i = 0; i < sz; i++)
//		{
//			dst[i] = src[i];
//		}
//	}
//}
//struct TrueType
//{
//	static bool Get()
//	{
//		return true;
//	}
//};
//struct FalseType
//{
//	static bool Get()
//	{
//		return false;
//	}
//};
////������ȡtypetraits
////1.ʹ����ģ���ģ���ػ���������������ȡ��typetraits,�ڲ���������falsetype
////2.�����Զ������ͣ�ͨ��ģ���ػ��Զ������͵�������ȡtypetraits,�ڲ���������truetype
////3.������ͨ��������������ɶ�Ӧ��typetraits,
////����truetype����falsetype��get()����ȷ������������Ƿ�Ϊ�Զ�������,���ݷ��ؽ�����������ķ�ʽ
////4.Ч�ʸߣ�����ʱȷ�����ͣ���ռ����ʱ��
//template<class T>
//struct TypeTraits
//{
//	typedef FalseType _isPodType;
//
//};
//template<>
//struct TypeTraits<char>
//{
//	typedef TrueType _isPodType;
//};
//template<>
//struct TypeTraits<int>
//{
//	typedef TrueType _isPodType;
//};
//template<>
//struct TypeTraits<double>
//{
//	typedef TrueType _isPodType;
//};
//template<>
//struct TypeTraits<float>
//{
//	typedef TrueType _isPodType;
//};
////......
//template<class T>
//void Copy(T* dst, const T* src, size_t sz)
//{
//	if (TypeTraits<T>::_isPodType::Get())
//	{
//		cout << typeid(T).name() << ":memcpy()" << endl;
//		memcpy(dst, src, sizeof(T)*sz);
//	}
//	else
//	{
//		cout << typeid(T).name() << ":operator=()" << endl;
//		for (size_t i = 0; i < sz; i++)
//		{
//			dst[i] = src[i];
//		}
//	}
//}
//int main()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
//	int arr2[7];
//	Copy(arr2, arr, 7);
//	string str1[] = { "123", "456", "hello", "world" };
//	string str2[4];
//	Copy(str2, str1, 4);
//	system("pause");
//	return 0;
//}
