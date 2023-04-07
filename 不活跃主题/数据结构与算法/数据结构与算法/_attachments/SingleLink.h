/**
 * 单向链表的定义
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
#include <stdlib.h>

template <typename Elem>
class SingleLink {
private:
	struct Node {
		Elem data;
		Node* next = NULL;
	};
	Node* _head;		// _head指针指向第一个节点。不设计头节点

public:
	SingleLink();
	~SingleLink();
	SingleLink(const SingleLink& l);
	SingleLink(SingleLink&& l);
	void operator=(SingleLink&& l);
	void operator=(const SingleLink& l);

	Bool IsEmpty();
	Status InsertElem(Elem e);
};


#pragma region 基本函数
template <typename Elem>
SingleLink<Elem>::SingleLink() {
	_head = NULL;
}

template <typename Elem>
SingleLink<Elem>::~SingleLink() {
	Node* p = _head;
	while (p) {
		Node* temp = p;
		p = p->next;
		delete temp;
	}
}

template <typename Elem>
SingleLink<Elem>::SingleLink(const SingleLink& l) {

	if (l._head) {
		_head = new Node();
		_head->data = l._head->data;

		Node* p = l._head->next;
		Node* q = _head;
		while (p) {
			Node* temp = new Node();
			temp->data = p->data;
			q->next = temp;
			q = temp;
			p = p->next;
		}
	}
	else _head = NULL;
}
template <typename Elem>
SingleLink<Elem>::SingleLink(SingleLink&& l) {
	_head = l._head;
	l._head = NULL;
}

template <typename Elem>
void SingleLink<Elem>::operator=(const SingleLink& l) {
	// 释放原来的内存
	Node* r = _head;
	while (r) {
		Node* temp = r;
		r = r->next;
		delete temp;
	}
	// 复制新的内容

	if (l._head) {
		_head = new Node();
		_head->data = l._head->data;

		Node* p = l._head->next;
		Node* q = _head;
		while (p) {
			Node* temp = new Node();
			temp->data = p->data;
			q->next = temp;
			q = temp;
			p = p->next;
		}
	}
	else _head = NULL;
}

template <typename Elem>
void SingleLink<Elem>::operator=(SingleLink&& l) {
	// 释放原来的内存
	Node* p = _head;
	while (p) {
		Node* temp = p;
		p = p->next;
		delete temp;
	}

	// 转移所有权
	_head = l._head;
	l._head = NULL;
}

#pragma endregion



/**
 * 链表是否为空
 */
template <typename Elem>
Bool SingleLink<Elem>::IsEmpty() {
	return _head == NULL ? TRUE : FALSE;
}

/**
 * 插入元素
 * 就在链首添加
 */
template <typename Elem>
Status SingleLink<Elem>::InsertElem(Elem e) {
	Node* n = new Node();
	n->data = e;
	n->next = _head;
	_head = n;
	return OK;
}