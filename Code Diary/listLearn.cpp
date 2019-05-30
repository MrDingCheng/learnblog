#include<iostream>
using namespace std;
template<class T>
struct ListNode
{
	ListNode(const T& val = T())
	:_next(nullptr)
	, _prev(nullptr)
	, _data(val)
	{}
	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;
};
template<class T,class Ref,class Ptr>
//通过封装节点，使用节点的操作完成迭代器的++，*，--，!=, ==功能
struct ListIterator
{
	typedef ListNode<T>* pNode;
	typedef ListIterator<T, T&, T*> self;
	pNode _node;
	ListIterator(pNode node = nullptr)
		:_node(node)
	{}
	T* operator->()
	{
		return &(_node->_data);
	}
	const T* operator->()const
	{
		return &(_node->_data);
	}
	//--iterator	
	self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	//iterator--
	self operator--(int)
	{
		self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	//++iterator
	self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	//iterator++
	self operator++(int)
	{
		self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	//*iterator
	//获取节点的_data
	T& operator*()
	{
		return _node->_data;
	}
	const T& operator*() const
	{
		return _node->_data;
	}
	//iterator != l.end()
	//比较两个迭代器封装的节点是否一样
	bool operator!=(self& it)
	{
		return _node != it._node;
	}
	bool operator==(self& it)
	{
		return _node == it._node;
	}
};
//template<class T>
//通过封装节点，使用节点的操作完成迭代器的++，*，--，!=, ==功能
//struct ConstListIterator
//{
//	typedef ListNode<T>* pNode;
//	typedef ConstListIterator<T> self;
//	pNode _node;
//	ConstListIterator(pNode node = nullptr)
//		:_node(node)
//	{}
//	const T* operator->() 
//	{
//		return &(_node->_data);
//	}
//	//--iterator	
//	self& operator--()
//	{
//		_node = _node->_prev;
//		return *this;
//	}
//	//iterator--
//	self operator--(int)
//	{
//		self tmp(*this);
//		_node = _node->_prev;
//		return tmp;
//	}
//	//++iterator
//	self& operator++()
//	{
//		_node = _node->_next;
//		return *this;
//	}
//	//iterator++
//	self operator++(int)
//	{
//		self tmp(*this);
//		_node = _node->_next;
//		return tmp;
//	}
//	//*iterator
//	//获取节点的_data
//	const T& operator*()
//	{
//		return _node->_data;
//	}
//	//iterator != l.end()
//	//比较两个迭代器封装的节点是否一样
//	bool operator!=(self& it)
//	{
//		return _node != it._node;
//	}
//	bool operator==(self& it)
//	{
//		return _node == it._node;
//	}
//};
template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef Node* pNode;
	typedef ListIterator<T,T&,T*> iterator;
	typedef ListIterator<const T,const T&,const T*> const_iterator;
	List(const T& val = T())
		:_head(new Node(val))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void Push_back(const T& val)
	{
		pNode curNode = new Node(val);
		pNode prev = _head->_prev;
		prev->_next = curNode;
		curNode->_prev = prev;
		curNode->_next = _head;
		_head->_prev = curNode;
	}
	void Pop_back()
	{
		pNode pDel = _head->_prev;
		if (pDel != _head){
			pDel->_prev->_next = _head;
			_head->_prev = pDel->_prev;
		}
	}
	iterator begin()
	{
		return iterator(_head->_next);
	}
	iterator end()
	{
		return iterator(_head);
	}
	const_iterator cbegin() const
	{
		return iterator(_head->_next);
	}
	const_iterator cend() const
	{
		return iterator(_head);
	}
	void Insert(iterator pos, const T& val)
	{
		pNode newNode = new Node(val);
		pNode cur = pos._node;
		pNode prev = cur->_prev;
		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = cur;
		cur->_prev = newNode;
	}
	iterator Erase(iterator pos)
	{
		pNode pDel = pos._node;
		pNode pRet = pDel->_next;
		pDel->_prev->_next = pDel->_next;
		pDel->_next->_prev = pDel->_prev;
		delete pDel;
		return iterator(pRet);
	}
	void Push_front(const T& val)
	{
		Insert(iterator(_head->_next), val);
	}
	void Pop_front()
	{
		if (_head->_prev!=_head)
			Erase(iterator(_head->_prev));
	}
	void Clear()
	{
		pNode pCur = _head->_next;
		while (pCur != _head)
		{
			_head->_next = pCur->_next;
			delete pCur;
			pCur = _head->_next;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
	void Swap(List<T> & l)
	{
		swap(_head, l._head);
	}
	~List()
	{
		Clear();
		delete _head;
		_head = nullptr;
	}
	bool Emtpy() const
	{
		return _head->_next == _head;
	}
	size_t Size() const
	{
		size_t count = 0;
		pNode pCur = _head->_next;
		while (pCur != _head)
		{
			++count;
			pCur = pCur->_next;
		}
		return count;
	}
	void Resize(size_t newSize, const T& val = T())
	{
		size_t oldSize = Size();
		if (oldSize <= newSize)
		{
			for (size_t i = oldSize; i < newSize; i++)
				Push_back(val);
		}
		else
		{
			for (size_t i = newSize; i < oldsize; ++i)
				Pop_back();
		}
	}
private:
	pNode _head;
};
int main()
{
	List<int> lst;
	lst.Push_back(1);
	lst.Push_back(2);
	lst.Push_back(3);
	lst.Push_back(4);
	lst.Pop_front();
	auto lit = lst.begin();
	while (lit != lst.end())
	{
		cout << *lit << " ";
		++lit;
	}
	cout << endl;
	system("pause");
	return 0;
}