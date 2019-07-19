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
		//�����Ϊ��,ֱ�Ӳ���
		if (_pRoot == nullptr){
			_pRoot = new Node(data);
			return true;
		}
		//����Ϊ�գ����ն��������������ʲ���data�����еĲ���λ��
		pNode pCur = _pRoot;
		//��¼pCur��˫�ף���Ϊ��Ԫ�����ղ�����pCur˫�����Һ��ӵ�λ��
		pNode pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else//Ԫ���Ѿ������д���
				return false;
		}
		//����Ԫ��
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		return true;
	}

	bool Erase(const T& data)
	{
		//�����Ϊ�գ�ɾ��ʧ��
		//����Ϊ�գ�����data�����е�λ��
		//���ҽ����
		//1.data�������У��޷�ɾ��
		//2.���ҵ��ˣ����������ɾ��
		//a)��ǰ�ڵ�ֻ�����ӻ�������Ϊ��--��ֱ��ɾ��
		//b)��ǰ�ڵ�ֻ���Һ���--��ֱ��ɾ��
		//c)��ǰ�ڵ����Һ��Ӷ��У���������������һ������ڵ㣬������ڵ��е�ֵ������ɾ���ڵ㣬ת����ɾ������ڵ�
		if (nullptr == _pRoot)
			return false;
		//����data�����е�λ��
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
		//data�������У��޷�ɾ��
		if (nullptr == pCur)
			return false;
		//��ǰ�ڵ�ֻ�����ӣ���������Ϊ��
		if (nullptr == pCur->_pRight)
		{
			if (pParent->_pLeft == pCur)
				pParent->_pLeft = pCur->_pLeft;
			else if (pParent->_pRight == pCur)
				pParent->_pRight = pCur->_pLeft;
			delete pCur;
		}
		//��ǰ�ڵ�ֻ��
	}
private:
	pNode _pRoot;
};
