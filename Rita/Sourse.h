#include <iostream>
#include <exception>
#include <stack>
#pragma once
#define BSTREE_EXCEPTION_BAD_INDEX "\n����������: ���� �� ������.\n"
#define BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE "\n����������: �������� �� ����������.\n"
#define BSTREE_EXCEPTION_COPY_NULLPTR "\n����������: root = nullptr.\n";

template <typename Td, typename Tk>
class BST
{
public:
	class Node
	{
	public:
		Node *left;
		Node *right;
		Node *parent;
		Tk key;
		Td data;
		bool color;
		long SubtreeSize;
		Node(Td _data, Tk _key); // : left(nullptr), right(nullptr), parent(nullptr),
		//						  key(_key), data(_data), color(false), SubtreeSize(0){};
		friend class BST<Td, Tk>; // added
	};
	// friend;
	Node *root;
	Node *tnil;
	long Counter = 0;
	long sizeT = 0;
	long _size(Node *node);
	void calcAll(Node *t);

private:
	void _copyNode(Node *node);
	void _clearNode(Node *node);
	void _printNode(Node *r, int level);
	void _printNode_TLR(Node *node);
	long _findOrder(Node *current, Tk key);

	Node *_findByKey(Tk key, Node *current);
	Node *_insertNode(Node *target, Tk key, Td data, bool *inserted);
	Node *_deleteNode(Node *t0);
	Node *_del(Node *t, Node *t0);
	Node *_delete(Node *t, int k, bool &deleted);

public:
	class BST_Iterator
	{
	public:
		Node *currentNode;
		BST *linkedTree;
		bool flagOutOfTree = false;
		BST_Iterator(BST<Td, Tk> *tree);
		BST_Iterator();
		Td &operator*();
		void operator++();
		void operator--();
		bool operator==(const BST_Iterator &otherTree);
		bool operator!=(const BST_Iterator &otherTree);
	};
	friend class BST_Iterator;

	class BST_R_Iterator
	{
	public:
		Node *currentNode;
		BST *linkedTree;
		bool flagOutOfTree = false;
		BST_R_Iterator();
		BST_R_Iterator(BST<Td, Tk> *tree);
		Td &operator*();
		void operator++();
		void operator--();
		bool operator==(const BST_R_Iterator &otherTree);
		bool operator!=(const BST_R_Iterator &otherTree);
	};
	friend class BST_R_Iterator;

	BST(){};
	BST(const BST<Td, Tk> &otherTree);
	~BST();
	long GetSizeT();
	void ClearTree();
	bool IsEmpty();
	bool InsertByKey(Td val, Tk key);
	bool DeleteByKey(Tk key);
	Td FindByKey(Tk key);
	bool Replace(Td val, Tk key);
	void Print();
	void Print_TLR();
	long GetCounter();
	void ClearCounter();
	long FindOrder(Tk key);

	Node *BSTSuccessor(Node *x);
	Node *BSTPredecessor(Node *x);
	Node *LParent(Node *t, Node *x);
	Node *RParent(Node *t, Node *x);
	BST_Iterator begin();
	BST_R_Iterator rbegin();
	BST_Iterator end();
	BST_R_Iterator rend();
};

// Define the Node class methods
template <typename Td, typename Tk>
BST<Td, Tk>::Node::Node(Td _data, Tk _key) : left(nullptr), right(nullptr), parent(nullptr),
											 key(_key), data(_data), color(false), SubtreeSize(0) {}

// ������������� color �� �����, ��� ��� ��� �������� ����� ��������������� � ������� ������� � �������� � ������, � �� ��� �������� ����
/*template <typename Td, typename Tk>
BST<Td, Tk>::Node::Node(Td _data, Tk _key)
{
	data = _data;
	key = _key;
	left = right = parent = nullptr;
	SubtreeSize = 1;
}*/

template <typename Td, typename Tk>
BST<Td, Tk>::BST(const BST<Td, Tk> &otherTree)
{
	if (&otherTree == nullptr)
		throw BSTREE_EXCEPTION_COPY_NULLPTR;
	root = nullptr;
	sizeT = 0;
	_copyNode(otherTree.root);
}

template <typename Td, typename Tk>
BST<Td, Tk>::~BST()
{

	if (root != nullptr)
		ClearTree();
}

template <typename Td, typename Tk>
void BST<Td, Tk>::_copyNode(Node *node)
{
	if (node == nullptr)
		return;
	InsertByKey(node->data, node->key);
	_copyNode(node->left);
	_copyNode(node->right);
}

template <typename Td, typename Tk>
long BST<Td, Tk>::GetSizeT()
{
	return sizeT;
}

template <typename Td, typename Tk>
void BST<Td, Tk>::ClearTree()
{
	_clearNode(root);
	root = nullptr;
}

template <typename Td, typename Tk>
void BST<Td, Tk>::_clearNode(Node *node)
{
	if (node == nullptr)
		return;
	if (node->left != nullptr)
	{
		_clearNode(node->left);
		node->left = nullptr;
	}
	if (node->right != nullptr)
	{
		_clearNode(node->right);
		node->right = nullptr;
	}
	delete node;
	sizeT = 0;
};

template <typename Td, typename Tk>
bool BST<Td, Tk>::IsEmpty()
{
	return (root == nullptr);
};

template <typename Td, typename Tk>
void BST<Td, Tk>::ClearCounter()
{
	Counter = 0;
};

template <typename Td, typename Tk>
long BST<Td, Tk>::GetCounter()
{
	return Counter;
};

//=======================================������===================================

template <typename Td, typename Tk>
void BST<Td, Tk>::Print()
{
	if (root != nullptr)
	{
		_printNode(root, 0);
	}
	else
		printf("\n� ������ ��� ���������\n");
};

template <typename Td, typename Tk>
void BST<Td, Tk>::Print_TLR()
{

	if (root != nullptr)
	{
		_printNode_TLR(root);
	}
	else
		printf("\n������ �� ����� ���������\n");
};

template <typename Td, typename Tk>
void BST<Td, Tk>::_printNode(Node *r, int level)

{
	if (r == nullptr)
		return;
	_printNode(r->right, level + 1);
	for (int i = 0; i <= level; i++)
		printf(" \t");
	printf("%i||%i\n\n", (int)(r->key), (int)(r->SubtreeSize));
	_printNode(r->left, level + 1);
}

template <typename Td, typename Tk>
void BST<Td, Tk>::_printNode_TLR(Node *node)

{
	if (node == nullptr)
		return;
	printf("����: %i: %i\n", (int)(node->key), (int)(node->data));
	if (node->left != nullptr)
		_printNode_TLR(node->left);
	if (node->right != nullptr)
		_printNode_TLR(node->right);
}

//==================================================��������====================================================

template <typename Td, typename Tk>
bool BST<Td, Tk>::DeleteByKey(Tk key)
{
	bool deleted = false;
	root = _delete(root, key, deleted);
	if (root != nullptr)
		sizeT = _size(root);
	else
		sizeT = 0;
	return deleted;
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::_deleteNode(Node *t0)
{
	delete t0;
	return nullptr;
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::_delete(Node *t, int k, bool &deleted)
{
	if (t == nullptr)
	{
		deleted = false;
		return t;
	}
	Counter++;
	if (k < t->key)
	{
		t->left = _delete(t->left, k, deleted);
		if (deleted)
			calcAll(t);
		return t;
	}
	if (k > t->key)
	{
		t->right = _delete(t->right, k, deleted);
		if (deleted)
			calcAll(t);
		return t;
	}
	deleted = true;
	if (t->left == nullptr && t->right == nullptr)
	{
		return _deleteNode(t);
	}
	if (t->left == nullptr)
	{
		Node *x = t->right;
		delete t;
		return x;
	}
	if (t->right == nullptr)
	{
		Node *x = t->left;
		delete t;
		return x;
	}
	t->right = _del(t->right, t);
	calcAll(t);
	return t;
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::_del(Node *t, Node *t0)
{
	Counter++;
	if (t->left != nullptr)
	{
		t->left = _del(t->left, t0);
		calcAll(t);
		return t;
	}
	t0->key = t->key;
	t0->data = t->data;
	Node *x = t->right;
	Counter++;
	delete t;
	return x;
}

//==================================================�������====================================================

template <typename Td, typename Tk>
bool BST<Td, Tk>::InsertByKey(Td val, Tk key)
{
	bool inserted = false;
	root = _insertNode(root, key, val, &inserted);
	if (inserted)
	{
		sizeT = _size(root);
	}
	return inserted;
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::_insertNode(Node *current, Tk key, Td data, bool *inserted)
{
	Counter++;
	if (current == nullptr)
	{
		current = new Node(data, key);
		*inserted = true;
		return current;
	}

	if (key == current->key)
	{
		*inserted = false;
		return current;
	}

	if (key < current->key)
	{
		current->left = _insertNode(current->left, key, data, inserted);
	}
	else
	{
		current->right = _insertNode(current->right, key, data, inserted);
	}

	*inserted = true;
	calcAll(current); // ����������� ������ ���������
	return current;
}

//==================================�����================================================
template <class Td, class Tk>
Td BST<Td, Tk>::FindByKey(Tk key)
{
	if (root == nullptr)
		throw(111);
	Node *targetNode = _findByKey(key, root);
	if (targetNode == NULL)
		throw(111);
	return targetNode->data;
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::_findByKey(Tk key, typename BST<Td, Tk>::Node *current)
{
	Counter++;
	if (current != nullptr)
	{
		if (current->key != key)
		{
			if (key < current->key)
				return _findByKey(key, current->left);
			else
				return _findByKey(key, current->right);
		}
	}
	return current;
}

template <typename Td, typename Tk>
bool BST<Td, Tk>::Replace(Td val, Tk key)
{
	Node *Target = _findByKey(key, root);
	if (Target == NULL)
		return false;
	Target->data = val;
	return true;
}

//======================�� ��������===================================
template <typename Td, typename Tk>
long BST<Td, Tk>::FindOrder(Tk key)
{
	return _findOrder(root, key);
}

template <typename Td, typename Tk>
long BST<Td, Tk>::_findOrder(Node *current, Tk key)
{
	if (current == nullptr)
	{
		throw 0;
		return 0;
	}
	if (key == current->key)
	{
		return _size(current->left) + 1;
	}
	if (key < current->key)
	{
		return _findOrder(current->left, key);
	}
	return _size(current->left) + 1 + _findOrder(current->right, key);
}

template <typename Td, typename Tk>
void BST<Td, Tk>::calcAll(Node *t) // ������������ ����������� ������� ������
{
	t->SubtreeSize = _size(t->left) + _size(t->right) + 1;
}

template <typename Td, typename Tk>
long BST<Td, Tk>::_size(Node *node)
{
	if (node == nullptr)
		return 0;
	return node->SubtreeSize;
}

//==========================================��������������� �������==========================
template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::BSTSuccessor(typename BST<Td, Tk>::Node *x)
{
	if (x == nullptr)
		return nullptr;
	if (x->right != nullptr)

	{
		Node *t = x->right;
		while (t->left != nullptr)
			t = t->left;
		return t;
	}
	else
		return LParent(root, x);
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::BSTPredecessor(typename BST<Td, Tk>::Node *x)
{
	if (x == nullptr)
		return nullptr;
	if (x->left != nullptr)

	{
		Node *t = x->left;
		while (t->right != nullptr)
			t = t->right;
		return t;
	}
	else
		return RParent(root, x);
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::LParent(typename BST<Td, Tk>::Node *t, typename BST<Td, Tk>::Node *x)
{
	if (t == x)
		return nullptr;
	if (x->key < t->key)
	{
		Node *rp = LParent(t->left, x);
		if (rp != nullptr)
			return rp;
		else
			return t;
	}
	else
		return LParent(t->right, x);
}

template <class Td, class Tk>
typename BST<Td, Tk>::Node *BST<Td, Tk>::RParent(typename BST<Td, Tk>::Node *t, typename BST<Td, Tk>::Node *x)
{
	if (t == x)
		return nullptr;

	if (x->key > t->key)
	{
		Node *rp = RParent(t->right, x);
		if (rp != nullptr)
			return rp;
		else
			return t;
	}
	else

		return RParent(t->left, x);
}

//====================================���������====================================
template <class Td, class Tk>
typename BST<Td, Tk>::BST_Iterator BST<Td, Tk>::begin()
{
	BST_Iterator iter = BST_Iterator(this);
	Node *cur = root;
	while (cur != nullptr && cur->left != nullptr)
		cur = cur->left;
	iter.currentNode = cur;
	return iter;
}

template <class Td, class Tk>
typename BST<Td, Tk>::BST_Iterator BST<Td, Tk>::end()
{
	BST_Iterator iter = BST_Iterator(this);
	Node *cur = root;
	if (cur != nullptr)
		while (cur->right != nullptr)
			cur = cur->right;
	iter.currentNode = cur;
	iter.flagOutOfTree = true;
	return iter;
}

template <class Td, class Tk>
typename BST<Td, Tk>::BST_R_Iterator BST<Td, Tk>::rbegin()
{
	BST_R_Iterator iter = BST_R_Iterator(this);
	Node *cur = root;
	if (cur != nullptr)
		while (cur->right != nullptr)
			cur = cur->right;
	iter.currentNode = cur;
	return iter;
}

template <class Td, class Tk>
typename BST<Td, Tk>::BST_R_Iterator BST<Td, Tk>::rend()
{
	BST_R_Iterator iter = BST_R_Iterator(this);
	Node *cur = root;
	if (cur != nullptr)
		while (cur->left != nullptr)
			cur = cur->left;
	iter.currentNode = cur;
	iter.flagOutOfTree = true;
	return iter;
}

template <typename Td, typename Tk>
BST<Td, Tk>::BST_Iterator::BST_Iterator(BST<Td, Tk> *tree)
{
	linkedTree = tree;
	currentNode = linkedTree->root;
}

template <typename Td, typename Tk>
BST<Td, Tk>::BST_Iterator::BST_Iterator()
{
	currentNode = NULL;
}

template <typename Td, typename Tk>
Td &BST<Td, Tk>::BST_Iterator::operator*()
{
	if (currentNode == NULL || flagOutOfTree)
	{
		throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
	}
	return currentNode->data;
}

template <typename Td, typename Tk>
void BST<Td, Tk>::BST_Iterator::operator++()
{
	Node *next = linkedTree->BSTSuccessor(currentNode);

	if (flagOutOfTree)
	{
		if (next == NULL)
		{
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
		else
			flagOutOfTree = false;
	}
	else
	{
		if (next != NULL)
		{
			currentNode = next;
		}
		else
		{
			flagOutOfTree = true;
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
	}
}

template <typename Td, typename Tk>
void BST<Td, Tk>::BST_Iterator::operator--()
{
	Node *next = linkedTree->BSTPredecessor(currentNode);
	if (flagOutOfTree)
	{
		if (next == NULL)
		{
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
		else
			flagOutOfTree = false;
	}
	else
	{
		if (next != NULL)
		{
			currentNode = next;
		}
		else
		{
			flagOutOfTree = true;
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
	}
}

template <typename Td, typename Tk>
bool BST<Td, Tk>::BST_Iterator::operator==(const BST_Iterator &otherTree)
{
	return currentNode == otherTree.currentNode && flagOutOfTree == otherTree.flagOutOfTree;
}

template <typename Td, typename Tk>
bool BST<Td, Tk>::BST_Iterator::operator!=(const BST_Iterator &otherTree)
{
	return currentNode != otherTree.currentNode && flagOutOfTree != otherTree.flagOutOfTree;
}

template <typename Td, typename Tk>
BST<Td, Tk>::BST_R_Iterator::BST_R_Iterator(BST<Td, Tk> *tree)
{
	linkedTree = tree;
	currentNode = linkedTree->root;
}

template <typename Td, typename Tk>
BST<Td, Tk>::BST_R_Iterator::BST_R_Iterator()
{
	currentNode = NULL;
}

template <typename Td, typename Tk>
Td &BST<Td, Tk>::BST_R_Iterator::operator*()
{
	if (currentNode == NULL || flagOutOfTree)
	{
		throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
	}
	return currentNode->data;
}

template <typename Td, typename Tk>
void BST<Td, Tk>::BST_R_Iterator::operator++()
{
	Node *next = linkedTree->BSTPredecessor(currentNode);
	if (flagOutOfTree)
	{
		if (next == NULL)
		{
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
		else
			flagOutOfTree = false;
	}
	else
	{
		if (next != NULL)
		{
			currentNode = next;
		}
		else
		{
			flagOutOfTree = true;
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
	}
}

template <typename Td, typename Tk>
void BST<Td, Tk>::BST_R_Iterator::operator--()
{
	Node *next = linkedTree->BSTSuccessor(currentNode);
	if (flagOutOfTree)
	{
		if (next == NULL)
		{
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
		else
			flagOutOfTree = false;
	}
	else
	{
		if (next != NULL)
		{
			currentNode = next;
		}
		else
		{
			flagOutOfTree = true;
			throw BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE;
		}
	}
}

template <typename Td, typename Tk>
bool BST<Td, Tk>::BST_R_Iterator::operator==(const BST_R_Iterator &otherTree)
{
	return currentNode == otherTree.currentNode && flagOutOfTree == otherTree.flagOutOfTree;
}

template <typename Td, typename Tk>
bool BST<Td, Tk>::BST_R_Iterator::operator!=(const BST_R_Iterator &otherTree)
{
	return currentNode != otherTree.currentNode && flagOutOfTree != otherTree.flagOutOfTree;
};
