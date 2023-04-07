/**
 * 队列的各种实现 
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


/**
 * 基于链表的队列实现
 */
template <typename Elem>
class LinkQueue {
private:
	struct Node {
		Elem data;
		Node* next;
	};
	Node* _head;
	Node* _rear;
public:
	LinkQueue() {
		// 有一个头节点
		_head = new Node();
		_head->next = NULL;
		_rear = _head;
	}
	~LinkQueue() {
		// 释放存放数据的节点
		Node* p = _head->next;
		while (p) {
			Node* temp = p;
			p = p->next;
			delete temp;
		}
		// 释放头节点
		delete _head;
	}
	Bool IsEmpty() {
		retrun _head == _rear ？ TRUE : FALSE;
	}
	Status EnQueue(Elem e) {
		// 生成节点
		Node* n = new Node();
		n->data = e;
		n->next = NULL;

		// 插入队列
		_rear->next = n;
		_rear = n;
		return OK;
	}
	Status DeQueue(Elem& e) {
		if (IsEmpty()) return ERROR;
		// 取出节点
		Node* temp = _head->next;
		e = temp->data;

		// 修改队列
		_head->next = temp->next;
		
		// 释放内存
		delete temp;
		return OK;
	}
};

/**
 * 基于顺序表的循环队列
 */
template <typename Elem, int MAX_SIZE>
class LoopQueue {
private:
	Elem* _base;
	int _head;
	int _rear;
public:
	LoopQueue() {
		_base = (Elem*)malloc((MAX_SIZE + 1) * sizeof(Elem));
		_head = 0;
		_rear = 0;
	}
	~LoopQueue() {
		_head = 0;
		_rear = 0;
		free(_base);
	}
	Bool IsEmpty() {
		return _head == _rear ? TRUE : FALSE;
	}
	Bool IsFull() {
		return (_rear + 1) % MAX_SIZE == _head ? TRUE : FALSE;
	}

	Status EnQueue(Elem e) {
		if (IsFull()) return ERROR;
		_base[_rear] = e;
		_rear = (_rear + 1) % MAX_SIZE;
		return OK;
	}
	Status DeQueue(Elem &e) {
		if (IsEmpty()) return ERROR;
		e = _base[_head];
		_head = (_head + 1) % MAX_SIZE;
		return OK;
	}
};