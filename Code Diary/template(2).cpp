#include<iostream>
using namespace std;
////类型模板参数
//template<class T1, typename T2>
//T1 Add(const T1& a, const T2& b)
//{
//	return a + b;
//}
////非类型模板参数：可当作一个常量使用
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
////const 修饰错位，const 修饰的a,b
//template<class T>
//bool isGreater(const T& a,const T& b)
//{
//	return a > b;
//}
////1.需要有一个已经存在的通用模板函数
////2.模板参数为空
////3.函数名后要显式写出要特化的类型
////4.特化的类型的格式要和通用的模板参数格式一致
////5.一般不去写函数模板的特化版本，函数模板的特化比较复杂，会报出一些奇怪的错误
//// 建议对于函数模板处理不了或者报错的，去实现一份对应类型的普通函数
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
//类模板特化
//		1.全特化
//		2.半特化
//template<class T1, class T2>
//class Data
//{
//public:
//	Data() { cout << "Data<T1, T2>" << endl; }
//private:
//	T1 _d1;
//	T2 _d2;
//};
////全特化
//template<>
//class Data<int, char>
//{
//public:
//	Data() { cout << "Data<int, char>" << endl; }
//private:
//	int _d1;
//	char _d2;
//};
////半特化
////1.部分特化
//template<class T>
//class Data<T, char>
//{
//public:
//	Data() { cout << "Data<T, char>" << endl; }
//private:
//	T _d1;
//	char _d2;
//};
////半特化
////2.对模板参数做进一步限制
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

//容器增容： 拷贝
//memcpy: 一片内存拷贝，效率高 ：O(1)
//赋值拷贝=：每个元素依次拷贝，效率较低: O(n)
//STL拷贝分两路：
//		1.内置类型：memcpy
//		2.自定义类型：赋值拷贝
//POD:Plain Old Data-->内置类型

//RTTI :Run Time Type Information/Identification
//RTTI :typeid(a).name() 运行时类型识别
//调用 isPODType(const char* tp):缺陷：效率较低，时间复杂度为O(n^2)
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
////类型萃取typetraits
////1.使用类模板和模板特化技术定义类型萃取类typetraits,内部定义类型falsetype
////2.对于自定义类型，通过模板特化自定义类型的类型萃取typetraits,内部定义类型truetype
////3.编译期通过输入的类型生成对应的typetraits,
////调用truetype或者falsetype的get()方法确定具体的类型是否为自定义类型,根据返回结果决定拷贝的方式
////4.效率高，编译时确定类型，不占运行时间
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
