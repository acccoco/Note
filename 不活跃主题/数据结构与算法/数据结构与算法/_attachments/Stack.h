/**
 * 栈的实现
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

/**
 * 顺序栈
 * 栈增长方向是高地址方向
 */
template <typename Elem>
class Stack {
private:
	Elem* _base;		// 栈基址
	Elem* _top;			// 栈顶
	int _size;
public:
	Stack();
	Stack(int size);
	Stack(const Stack& s);
	Stack(Stack&& s);
	~Stack();
	void operator=(const Stack& s);
	void operator=(Stack&& s);

	Bool IsEmpty();
	Bool IsFull();
	Status Push(Elem e);
	Status Pop(Elem& e);
	Status Top(Elem& e);
};


#pragma region 基本函数
template <typename Elem>
Stack<Elem>::Stack() {
	_base = NULL;
	_top = NULL;
	_size = 0;
}
template <typename Elem>
Stack<Elem>::Stack(int size) {
	if (size <= 0) throw(0);
	_base = new Elem[size];
	_top = _base;
	_size = size;
}
template <typename Elem>
Stack<Elem>::Stack(const Stack& s) {
	_size = s._size;
	_base = new Elem[_size];
	_top = _base;

	for (Elem* p = s._base; s < s._top; s++) {
		*_top = *p;
		_top++;
	}
}
template <typename Elem>
Stack<Elem>::Stack(Stack&& s) {
	_base = s._base;
	_top = s._top;
	_size = s._size;

	s._base = NULL;
}
template <typename Elem>
Stack<Elem>::~Stack() {
	delete[] _base;
}
template <typename Elem>
void Stack<Elem>::operator=(const Stack& s) {
	// 删除原内存
	delete[] _base;

	// 复制新内容
	_size = s._size;
	_base = new Elem[_size];
	_top = _base;

	for (Elem* p = s._base; s < s._top; s++) {
		*_top = *p;
		_top++;
	}
}
template <typename Elem>
void Stack<Elem>::operator=(Stack&& s) {
	// 删除源内存
	delete[] _base;

	// 接管新内容
	_base = s._base;
	_top = s._top;
	_size = s._size;

	// xx
	s._base = NULL;
}
#pragma endregion

/**
 * 栈是否为空
 */
template <typename Elem>
Bool Stack<Elem>::IsEmpty() {
	return _base == _top ? TRUE : FALSE;
}

/**
 * 栈是否满
 */
template <typename Elem>
Bool Stack<Elem>::IsFull() {
	int current = (_top - _base) / sizeof(Elem);
	if (current == _size) return TRUE;
	else return FALSE;
}

/**
 * 入栈
 */
template <typename Elem>
Status Stack<Elem>::Push(Elem e) {
	if (IsFull()) return ERROR;
	*_top = e;
	_top++;
	return OK;
}

/**
 * 出栈
 */
template <typename Elem>
Status Stack<Elem>::Pop(Elem& e) {
	if (IsEmpty()) return ERROR;
	_top--;
	e = *_top;
	return OK;
}

/**
 * 获得栈顶的元素
 */
template <typename Elem>
Status Stack<Elem>::Top(Elem& e) {
	if (IsEmpty()) return ERROR;

	e = *(_top - 1);
	return OK;
}