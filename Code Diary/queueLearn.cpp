#include<iostream>
#include<deque>
#include<list>
#include<queue>
using namespace std;
template<class T, class Con = deque<T>>
class Queue
{
public:
	void Push(const T& x)
	{
		_con.push_back(x);
	}
	void Pop()
	{
		_con.pop_front();
	}
	T& Front()
	{
		return _con.front();
	}
	size_t Size()
	{
		return _con.size();
	}
	bool Empty()
	{
		return _con.empty();
	}
	T& Back()
	{
		return _con.back();
	}
private:
	Con _con;
};
//int main()
//{
//	Queue<int, list<int> > q;
//	q.Push(1);
//	q.Push(2);
//	q.Push(3);
//	q.Push(4);
//	q.Push(5);
//	while (!q.Empty())
//	{
//		cout << q.Front() << " ";
//		q.Pop();
//	}
//	cout << endl;
//	system("pause");
//	return 0;
//}
//仿函数（函数对象）：重载“()”运算符

//int main()
//{
//	Greater g;
//	cout << g(2, 3) << endl;
//	priority_queue<int, vector<int>, Greater> d;
//	d.push(1);
//	d.push(2);
//	d.push(5);
//	d.push(3);
//	while (!d.empty())
//	{
//		cout << d.top() << " ";
//		d.pop();
//	}
//	system("pause");
//	return 0;
//}