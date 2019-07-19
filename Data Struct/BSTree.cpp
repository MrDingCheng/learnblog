template<class T>
struct BSTNode
{
	BSTNode(const T& data = T())
	:_pLeft(nullptr)
	, _pRight(nullptr)
	, _data(data)
	{}

	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;
	T _data;

};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
	typedef Node* pNode;
public:
	BSTree()
		:_pRoot(nullptr)
	{}

	~BSTree()
	{
		_Destroy(_pRoot);
	}

	bool Insert(const T& data)
	{
		//如果树为空,直接插入
		if (_pRoot == nullptr){
			_pRoot = new Node(data);
			return true;
		}
		//树不为空，按照二叉搜索树的性质查找data在树中的插入位置
		pNode pCur = _pRoot;
		//记录pCur的双亲，因为新元素最终插入在pCur双亲左右孩子的位置
		pNode pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else//元素已经在树中存在
				return false;
		}
		//插入元素
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		return true;
	}

	bool Erase(const T& data)
	{
		//如果树为空，删除失败
		//树不为空，查找data在树中的位置
		//查找结果：
		//1.data不在树中，无法删除
		//2.查找到了，分以下情况删除
		//a)当前节点只有左孩子或者左孩子为空--可直接删除
		//b)当前节点只有右孩子--可直接删除
		//c)当前节点左右孩子都有，先在其子树中找一个替代节点，将替代节点中的值交给待删除节点，转换成删除替代节点
		if (nullptr == _pRoot)
			return false;
		//查找data在树中的位置
		pNode pCur = _pRoot;
		pNode pParent = nullptr;
		while (pCur)
		{
			if (data == pCur->_data)
				break;
			else if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}
		//data不在树中，无法删除
		if (nullptr == pCur)
			return false;
		//当前节点只有左孩子，或者左孩子为空
		if (nullptr == pCur->_pRight)
		{
			if (pParent->_pLeft == pCur)
				pParent->_pLeft = pCur->_pLeft;
			else if (pParent->_pRight == pCur)
				pParent->_pRight = pCur->_pLeft;
			delete pCur;
		}
		//当前节点只有
	}
private:
	pNode _pRoot;
};
