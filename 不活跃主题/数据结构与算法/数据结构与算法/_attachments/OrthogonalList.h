// 十字链表 - 造轮子


/**
 * 十字链表的定义
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
class CrossLink {
private:
	struct Node {
		Elem data;
		int i = -1;
		int j = -1;
		Node* right = NULL;
		Node* down = NULL;
	};
	Node** _row_head = NULL;
	Node** _col_head = NULL;
	int _row = 0;
	int _col = 0;
public:
	CrossLink();
	~CrossLink();
	CrossLink(int row, int col);
	CrossLink(const CrossLink& l);
	CrossLink(CrossLink&& l);
	void operator=(const CrossLink& l);
	void operator=(CrossLink&& l);

	Status Insert(Elem e, int i, int j);
};

#pragma region 基本函数
template <typename Elem>
CrossLink<Elem>::CrossLink() {
	// do nothing
}
template <typename Elem>
CrossLink<Elem>::~CrossLink() {
	// 释放元素内存
	for (int i = 0; i < _row; i++) {
		Node* p = _row_head[i];
		while (p) {
			Node* temp = p;
			p = p->right;
			delete temp;
		}
	}

	// 释放头指针内存
	delete[] _row_head;
	delete[] _col_head;
}


template <typename Elem>
CrossLink<Elem>::CrossLink(int row, int col) {
	if (row <= 0 || col <= 0) throw(0);

	_row = row;
	_col = col;
	_row_head = new Node * [row];
	_col_head = new Node * [col];
	for (int i = 0; i < _row; i++) _row_head[i] = NULL;
	for (int i = 0; i < _col; i++) _col_head[i] = NULL;
}

template <typename Elem>
CrossLink<Elem>::CrossLink(const CrossLink& l) {
	_row = l._row;
	_col = l._col;
	_row_head = new Node * [_row];
	_col_head = new Node * [_col];
	for (int i = 0; i < _row; i++) _row_head[i] = NULL;
	for (int i = 0; i < _col; i++) _col_head[i] = NULL;


	// 需要一个辅助数组，存放列链的链尾；以及一个辅助指针，存放当前行链的链尾
	Node** col_tail = new Node * [l._col];
	Node* row_tail;
	// 初始化列链链尾
	for (int i = 0; i < l._col; i++) col_tail[i] = NULL;

	for (int i = 0; i < l._row; i++) {
		// 初始化行链链尾
		row_tail = NULL;

		Node* p = l._row_head[i];
		while (p) {
			int ni = p->i;
			int nj = p->j;

			Node* temp = new Node();
			temp->i = ni;
			temp->j = nj;
			temp->data = p->data;

			if (row_tail == NULL) _row_head[ni] = temp;
			else row_tail->right = temp;
			if (col_tail[nj] == NULL) _col_head[nj] = temp;
			else col_tail[nj]->down = temp;
			row_tail = temp;
			col_tail[nj] = temp;

			p = p->right;
		}
	}

	delete[] col_tail;
}
template <typename Elem>
CrossLink<Elem>::CrossLink(CrossLink&& l) {
	// 释放原来的内存
	for (int i = 0; i < _row; i++) {
		Node* p = _row_head[i];
		while (p) {
			Node* temp = p;
			p = p->right;
			delete temp;
		}
	}
	delete[] _row_head;
	delete[] _col_head;
	// 获取新的内容即可
	_row = l._row;
	_col = l._col;
	_row_head = l._row_head;
	_col_head = l._col_head;
	l._row_head = NULL;
	l._col_head = NULL;
}
template <typename Elem>
void CrossLink<Elem>::operator=(const CrossLink& l) {
	// 释放原来内存
	for (int i = 0; i < _row; i++) {
		Node* p = _row_head[i];
		while (p) {
			Node* temp = p;
			p = p->right;
			delete temp;
		}
	}
	delete[] _row_head;
	delete[] _col_head;
	// 复制新的内容
	_row = l._row;
	_col = l._col;
	_row_head = new Node * [_row];
	_col_head = new Node * [_col];
	for (int i = 0; i < _row; i++) _row_head[i] = NULL;
	for (int i = 0; i < _col; i++) _col_head[i] = NULL;

	// 需要一个辅助数组，存放列链的链尾；以及一个辅助指针，存放当前行链的链尾
	Node** col_tail = new Node * [l._col];
	Node* row_tail;
	// 初始化列链链尾
	for (int i = 0; i < l._col; i++) col_tail[i] = NULL;

	for (int i = 0; i < l._row; i++) {
		// 初始化行链链尾
		row_tail = NULL;

		Node* p = l._row_head[i];
		while (p) {
			Node* temp = new Node();
			int ni = p->i;
			int nj = p->j;
			temp->i = ni;
			temp->j = nj;
			temp->data = p->data;

			if (row_tail == NULL) _row_head[ni] = temp;
			else row_tail->right = temp;
			if (col_tail[nj] == NULL) _col_head[nj] = temp;
			else col_tail[nj]->down = temp;
			row_tail = temp;
			col_tail[nj] = temp;

			p = p->right;
		}
	}

	delete[] col_tail;
}
template <typename Elem>
void CrossLink<Elem>::operator=(CrossLink&& l) {
	_row = l._row;
	_col = l._col;
	_row_head = l._row_head;
	_col_head = l._col_head;
	l._row_head = NULL;
	l._col_head = NULL;
}
#pragma endregion


/**
 * 插入元素，不考虑覆盖的情况
 */
template <typename Elem>
Status CrossLink<Elem>::Insert(Elem e, int i, int j) {
	if (i < 0 || i >= _row || j < 0 || j >= _col) throw(0);

	Node* new_node = new Node();
	new_node->i = i;
	new_node->j = j;
	new_node->data = e;

	// 行链头不存在
	if (!_row_head[i]) {
		_row_head[i] = new_node;
	}
	// 行链头在当前节点之后
	else if (_row_head[i]->j > j) {
		new_node->right = _row_head[i];
		_row_head[i] = new_node;
	}
	// 行链头存在，且在当前节点之前
	else {
		Node* p = _row_head[i];
		while (p) {
			Node* temp = p->right;
			if (!temp || temp->j > j) {
				new_node->right = p->right;
				p->right = new_node;
				break;
			}
		}
	}

	// 列操作，同行操作
	if (!_col_head[j]) {
		_col_head[j] = new_node;
	}
	else if (_col_head[j]->i > i) {
		new_node->down = _col_head[j];
		_col_head[j] = new_node;
	}
	else {
		Node* p = _col_head[j];
		while (p) {
			Node* temp = p->down;
			if (!temp || temp->i > i) {
				new_node->down = p->down;
				p->down = new_node;
				break;
			}
		}
	}

	return OK;
}