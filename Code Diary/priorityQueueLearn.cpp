#include<iostream>
#include<vector>
using namespace std;
template<class T>
class Greater
{
public:
	bool operator()(const T& a, const T& b)
	{
		return a < b;
	}
};
template<class T,class Container = vector<T>,class Compare = Greater<T>>
class PriorityQueue
{
public:
	void Push(const T& val)
	{
		//先把元素放到数组的最后一个位置
		_con.push_back(val);
		//向上调整，使数组满足堆的性质
		ShiftUp(_con.size()-1);
	}
	void ShiftUp(size_t child)
	{
		//和父节点比较大小
		Compare _cmp;
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			//if (_con[child] > _con[parent])
			if (_cmp(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				//更新父子节点位置
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	void ShiftDown(size_t parent)
	{
		Compare _cmp;
		size_t child = 2 * parent + 1;
		while (child < _con.size())
		{
			int max = child;
			//if (child + 1 < _con.size() && _con[child + 1] > _con[child])
			if (child + 1 < _con.size() && _cmp(_con[child], _con[child+1]))	
			{
				max = child + 1;
			}
			if (_cmp(_con[parent], _con[child]))
			{
				swap(_con[max], _con[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
		//如果右孩子存在，且大于左孩子的值，拿右孩子的值
	}
	void Pop()
	{
		//交换根元素和最后一个叶子节点元素
		swap(_con[0], _con[_con.size() - 1]);
		//删除最后一个元素
		_con.pop_back();
		//从根部向下调整，使其满足堆的性质
		ShiftDown(0);
	}
	T& Top()
	{
		return _con[0];
	}
	bool Empty()
	{
		return _con.empty();
	}
private:
	Container _con;
};
int main()
{
	PriorityQueue<int,vector<int>,Greater<int>> p;
	p.Push(1);
	p.Push(3);
	p.Push(5);
	p.Push(2);
	while (!p.Empty())
	{
		cout << p.Top() << " ";
		p.Pop();
	}
	cout << endl;
	union Un1
	{
		char c[5];
		int i;
	};
	union Un2
	{
		short c[7];
		int i;
	};
	printf("%d\n", sizeof(union Un1));
	printf("%d\n", sizeof(union Un2));
	system("pause");
	return 0;
}