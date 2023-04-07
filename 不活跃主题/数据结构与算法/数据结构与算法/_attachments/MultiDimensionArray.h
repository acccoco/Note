/**
 * 多维数组的定义
 * 实现了五类基本元素，较为稳定
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
#include <stdarg.h>
template <typename Elem>
class MulArray {
private:
#define MAX_ARRAY_DIM 8
	Elem* _base;		// 数组的基址
	int _dim;			// 数组的维度
	int* _length;		// 每一个维度的长度信息
public:
	MulArray();
	MulArray(int dim, ...);
	~MulArray();
	MulArray(const MulArray& arr);
	MulArray(MulArray&& arr);
	void operator=(const MulArray& arr);
	void operator=(MulArray&& arr);

	Elem& Value(int dim, ...);
};

#pragma region 基本函数
template <typename Elem>
MulArray<Elem>::MulArray() {
	_base = NULL;
	_dim = 0;
	_length = NULL;
}


/**
 * 基本的构造函数
 * 变长参数类型均为int
 */
template <typename Elem>
MulArray<Elem>::MulArray(int dim, ...) {
	if (dim < 1 || dim > MAX_ARRAY_DIM) throw(0);
	_dim = dim;
	_length = new int[dim];

	// 计算元素总数
	int total_elem = 1;
	va_list ap;
	va_start(ap, dim);
	for (int i = 0; i < dim; i++) {
		_length[i] = va_arg(ap, int);
		if (_length[i] <= 0) throw(0);
		total_elem *= _length[i];
	}
	va_end(ap);

	// 分配内存
	_base = new Elem[total_elem];
}

/**
 * 基本的析构函数
 */
template <typename Elem>
MulArray<Elem>::~MulArray() {
	delete[] _length;
	delete[] _base;
}

template <typename Elem>
MulArray<Elem>::MulArray(const MulArray& arr) {
	// 分配内存
	_dim = arr._dim;
	_length = new int[_dim];
	int total_elem = 1;
	for (int i = 0; i < _dim; i++) {
		_length[i] = arr._length[i];
		total_elem *= _length[i];
	}
	_base = new Elem[total_elem];

	// 复制元素
	for (int i = 0; i < total_elem; i++) {
		_base[i] = arr._base[i];
	}
}

template <typename Elem>
MulArray<Elem>::MulArray(MulArray&& arr) {
	_dim = arr._dim;
	_length = arr._length;
	_base = arr._base;

	arr._length = NULL;
	arr._base = NULL;
}


template <typename Elem>
void MulArray<Elem>::operator=(const MulArray& arr) {
	// 释放原先的内存
	delete _length;
	delete _base;

	// 分配新内存
	_dim = arr._dim;
	_length = new int[_dim];
	int total_elem = 1;
	for (int i = 0; i < _dim; i++) {
		_length[i] = arr._length[i];
		total_elem *= _length[i];
	}
	_base = new Elem[total_elem];

	// 复制元素
	for (int i = 0; i < total_elem; i++) {
		_base[i] = arr._base[i];
	}
}
template <typename Elem>
void MulArray<Elem>::operator=(MulArray&& arr) {
	// 释放原先的内存
	delete[] _length;
	delete[] _base;

	// 复制新的
	_dim = arr._dim;
	_length = arr._length;
	_base = arr._base;

	// xx
	arr._length = NULL;
	arr._base = NULL;
}
#pragma endregion





/**
 * 访问某个数组元素
 * @param dim 维度
 */
template <typename Elem>
Elem& MulArray<Elem>::Value(int dim, ...) {
	if (dim != _dim) throw(0);

	va_list ap;
	va_start(ap, dim);
	int pos = 0;
	for (int i = 0; i < dim; i++) {
		pos *= _length[i];
		int current_pos = va_arg(ap, int);
		if (current_pos < 0 || current_pos >= _length[i]) throw(0);
		pos += current_pos;
	}

	return _base[pos];
}