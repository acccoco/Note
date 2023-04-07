/**
 * 二叉链：二叉树的链实现
 */

#pragma once
typedef int Bool;
#define TRUE 1
#define FALSE 0

typedef int Status;
#define OK 1
#define ERROR 0

#ifndef NULL
#define NULL 0
#endif // !NULL
#include <stack>
using namespace std;

template <typename Elem>
class BinaryLink {
public:
	typedef Status(*Visit)(const BinaryLink& node);
private:

	BinaryLink* _lchild = NULL;
	BinaryLink* _rchild = NULL;
	Elem _data;
	
	void _Destroy(BinaryLink* l);
	void _Copy(const BinaryLink* s, BinaryLink* t);
public:
	BinaryLink();
	BinaryLink(Elem e);
	~BinaryLink();
	BinaryLink(const BinaryLink& l);
	BinaryLink(BinaryLink&& l);
	void operator=(const BinaryLink& l);
	void operator=(BinaryLink&& l);

	
	Status static _InOrderTraverse(BinaryLink* l, Visit visit);
	Status InOrderTraverse(Visit visit);
	Status InOrderTraverse_iter(Visit visit);
	Status InOrderTraverse_iter2(Visit visit);
	Status static _PostOrderTraverse(BinaryLink* l, Visit visit);
	Status PostOrderTraverse(Visit visit);
	Status PostOrderTraverse_iter(Visit visit);

	Elem GetElem() const;
	Status InsertLeaf(Elem e, int l_r);
	Status Insert(BinaryLink* l, int l_r);
	BinaryLink* GetLeft();
	BinaryLink* GetRight();
};

/**
 * 用于析构的辅助函数
 * 用于销毁一颗树
 */
template <typename Elem>
void BinaryLink<Elem>::_Destroy(BinaryLink* l) {
	if (!l) return;
	_Destroy(l->_lchild);
	l->_lchild = NULL;
	_Destroy(l->_rchild);
	l->_rchild = NULL;
	delete l;
}

/**
 * 用于复制的辅助函数
 * s需要不为NULl
 */
template <typename Elem>
void BinaryLink<Elem>::_Copy(const BinaryLink* s, BinaryLink* t) {
	if (s->_lchild) {
		BinaryLink* temp = new BinaryLink();
		t->_lchild = temp;
		_Copy(s->_lchild, temp);
	}
	if (s->_rchild) {
		BinaryLink* temp = new BinaryLink();
		t->_rchild = temp;
		_Copy(s->_rchild, temp);
	}
	t->_data = s->_data;
}

#pragma region 基本函数
template <typename Elem>
BinaryLink<Elem>::BinaryLink() {
	// do nothing
}
template <typename Elem>
BinaryLink<Elem>::BinaryLink(Elem e) {
	_data = e;
}
template <typename Elem>
BinaryLink<Elem>::~BinaryLink() {
	if (_lchild) {
		_Destroy(_lchild);
		_lchild = NULL;
	}
	if (_rchild) {
		_Destroy(_rchild);
		_rchild = NULL;
	}
}
template <typename Elem>
BinaryLink<Elem>::BinaryLink(const BinaryLink& l) {
	_data = l._data;
	if (l._lchild) {
		BinaryLink* temp = new BinaryLink();
		_lchild = temp;
		_Copy(l._lchild, temp);
	}
	if (l._rchild) {
		BinaryLink* temp = new BinaryLink();
		_rchild = temp;
		_Copy(l._rchild, temp);
	}
}
template <typename Elem>
BinaryLink<Elem>::BinaryLink(BinaryLink&& l) {

	// 复制新的
	_data = l._data;
	_lchild = l._lchild;
	_rchild = l._rchild;

	// xx
	l._lchild = NULL;
	l._rchild = NULL;
}
template <typename Elem>
void BinaryLink<Elem>::operator=(const BinaryLink& l) {
	// 释放原来的内存
	if (_lchild) {
		_Destroy(_lchild);
		_lchild = NULL;
	}
	if (_rchild) {
		_Destroy(_rchild);
		_rchild = NULL;
	}

	// 复制新的
	_data = l._data;
	if (l._lchild) {
		BinaryLink* temp = new BinaryLink();
		_lchild = temp;
		_Copy(l._lchild, temp);
	}
	if (l._rchild) {
		BinaryLink* temp = new BinaryLink();
		_rchild = temp;
		_Copy(l._rchild , temp);
	}
}
template <typename Elem>
void BinaryLink<Elem>::operator=(BinaryLink&& l) {
	// 释放原来的内存
	if (_lchild) {
		_Destroy(_lchild);
		_lchild = NULL;
	}
	if (_rchild) {
		_Destroy(_rchild);
		_rchild = NULL;
	}

	// 复制新的
	_data = l._data;
	_lchild = l._lchild;
	_rchild = l._rchild;

	// xx
	l._lchild = NULL;
	l._rchild = NULL;
}
#pragma endregion


template <typename Elem>
Elem BinaryLink<Elem>::GetElem() const {
	return _data;
}

/**
 * 中序遍历
 */
template <typename Elem>
Status BinaryLink<Elem>::InOrderTraverse(Visit visit) {
	return _InOrderTraverse(this, visit);
}
template <typename Elem>
Status BinaryLink<Elem>::_InOrderTraverse(BinaryLink* l, Visit visit) {
	if (!l) return OK;
	_InOrderTraverse(l->_lchild, visit);
	visit(*l);
	_InOrderTraverse(l->_rchild, visit);
	return OK;
}
/**
 * 中序遍历：递归向迭代的机械转换
 */
template <typename Elem>
Status BinaryLink<Elem>::InOrderTraverse_iter2(Visit visit) {
	struct frame {
		int label = 0;
		BinaryLink* node = NULL;
		frame() {}
		frame(int l, BinaryLink* b) : label(l), node(b) {}
	};
	// 初始化工作栈
	stack<frame> s = stack<frame>(256);

	s.Push(frame(3, this));
	frame top = frame();
// if (!l) return OK;
label_0:
	s.Top(top);
	if (top.node == NULL) goto label_3;
// _InOrderTraverse(l->_lchild, visit);
	s.Push(frame(1, top.node->_lchild));
	goto label_0;
label_1:
	s.Pop(top);
	s.Top(top);
// visit(*l);
	visit(*(top.node));
// _InOrderTraverse(l->_rchild, visit);
	s.Push(frame(2, top.node->_rchild));
	goto label_0;
label_2:
	s.Pop(top);
	s.Top(top);
label_3:
	s.Top(top);
// end
	switch (top.label)
	{
	case 0: goto label_0;
		break;
	case 1: goto label_1;
		break;
	case 2: goto label_2;
		break;
	case 3: s.Top(top);
		break;
	}

	return OK;
}
/**
 * 中序遍历的迭代写法
 */
template <typename Elem>
Status BinaryLink<Elem>::InOrderTraverse_iter(Visit visit) {
	stack<BinaryLink*> s = stack<BinaryLink*>(256);

	BinaryLink* c = this;
	while (c || !s.IsEmpty()) {
		if (c) {
			s.Push(c);
			c = c->_lchild;
		}
		else {
			s.Pop(c);
			visit(*c);
			c = c->_rchild;
		}
	}

	return OK;
}

/**
 * 后序遍历
 */
template <typename Elem>
Status BinaryLink<Elem>::PostOrderTraverse(Visit visit) {
	return _PostOrderTraverse(this, visit);
}
template <typename Elem>
Status BinaryLink<Elem>::_PostOrderTraverse(BinaryLink* l, Visit visit) {
	if (!l) return OK;
	_PostOrderTraverse(l->_lchild, visit);
	_PostOrderTraverse(l->_rchild, visit);
	visit(*l);
	return OK;
}
template <typename Elem>
Status BinaryLink<Elem>::PostOrderTraverse_iter(Visit visit) {
	struct frame {
		int label = 0;
		BinaryLink* node = NULL;
		frame() {}
		frame(int l, BinaryLink* b): label(l), node(b) {}
	};
	// 初始化工作栈
	stack<frame> s = stack<frame>(256);


	s.Push(frame(3, this));			// 初始内容
	frame top = frame();			// 存放变量
// if (!l) return OK;
label_0:
	s.Top(top);
	if (top.node == NULL) goto label_3;
// _PostOrderTraverse(l->_lchild, visit);
	s.Push(frame(1, top.node->_lchild));
	goto label_0;
label_1:
	s.Pop(top);
	s.Top(top);
// _PostOrderTraverse(l->_rchild, visit);
	s.Push(frame(2, top.node->_rchild));
	goto label_0;
label_2:
	s.Pop(top);
	s.Top(top);
// visit(*l);
	visit(*(top.node));
// end
label_3:
	s.Top(top);
	switch (top.label)
	{
	case 0: goto label_0;
		break;
	case 1: goto label_1;
		break;
	case 2: goto label_2;
		break;
	case 3: s.Pop(top);
		break;
	}

	return OK;
}

/**
 * 插入值作为左叶子或右叶子
 * 左为1，右为2
 */
template <typename Elem>
Status BinaryLink<Elem>::InsertLeaf(Elem e, int l_r) {
	if (l_r == 1 && !_lchild) {
		_lchild = new BinaryLink(e);
	}
	if (l_r == 2 && !_rchild) {
		_rchild = new BinaryLink(e);
	}
	return OK;
}


/**
 * 插入一整颗树作为子节点
 */
template <typename Elem>
Status BinaryLink<Elem>::Insert(BinaryLink* l, int l_r) {
	if (l_r == 1 && !_lchild) {
		_lchild = l;
	}
	if (l_r == 2 && !_rchild) {
		_rchild = l;
	}

	return OK;
}

/**
 * 获得左子树
 */
template <typename Elem>
BinaryLink<Elem>* BinaryLink<Elem>::GetLeft() {
	return _lchild;
}

/**
 * 获得右子树
 */
template <typename Elem>
BinaryLink<Elem>* BinaryLink<Elem>::GetRight() {
	return _rchild;
}