/**
 * 一维数组的实现
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
  * INCREMENT表示：当分配的内存空间不够用时，应该再要求分配多大的空间
  */
template <typename Elem, size_t INCREAMENT = 10>
class Array {
private:
	Elem* _base;			// 数组基址
	size_t _length;			// 数组长度
	size_t _size;			// 数组的最大尺寸
	void Expand();
public:
	Array();
	Array(size_t size);
	~Array();
	Array(const Array& arr);
	Array(Array&& arr);
	void operator=(const Array& arr);
	void operator=(Array&& arr);


	size_t Length();
	Status Insert(const Elem e);
	Status Delete(Elem& e);
	Elem& operator[](const size_t index);
	Status Resize(size_t length);
};

#pragma region 基本函数
template <typename Elem, size_t INCREAMENT>
Array<Elem, INCREAMENT>::Array() {
	_base = NULL;
	_length = 0;
	_size = 0;
}

template <typename Elem, size_t INCREAMENT>
Array<Elem, INCREAMENT>::Array(size_t size) {
	_base = new Elem(size);
	_length = size;
	_size = size;
}

template <typename Elem, size_t INCREAMENT>
Array<Elem, INCREAMENT>::~Array() {
	delete[] _base;
}

template <typename Elem, size_t INCREAMENT>
Array<Elem, INCREAMENT>::Array(const Array& arr) {
	// 分配内存
	_length = arr._length;
	_size = arr._size;
	_base = new Elem[_size];

	// 复制元素
	for (size_t i = 0; i < _length; i++) {
		_base[i] = arr._base[i];
	}
}

template <typename Elem, size_t INCREAMENT>
Array<Elem, INCREAMENT>::Array(Array&& arr) {
	_length = arr._length;
	_size = arr._size;
	_base = arr._base;

	arr._base = NULL;
}

template <typename Elem, size_t INCREAMENT>
void Array<Elem, INCREAMENT>::operator=(const Array& arr) {
	// 释放原来的内存
	delete[] _base;

	// 分配新的
	_length = arr._length;
	_size = arr._size;
	_base = new Elem[_size];

	// 复制元素
	for (size_t i = 0; i < _length; i++) {
		_base[i] = arr._base[i];
	}
}

template <typename Elem, size_t INCREAMENT>
void Array<Elem, INCREAMENT>::operator=(Array&& arr) {
	// 释放原来的内存
	delete[] _base;

	// 分配新的
	_length = arr._length;
	_size = arr._size;
	_base = arr._base;

	// xx
	arr._base = NULL;
}
#pragma endregion

/**
 * 扩充数组尺寸
 */
template <typename Elem, size_t INCREAMENT>
void Array<Elem, INCREAMENT>::Expand() {
	// 分配新的内存
	size_t new_size = _size + INCREAMENT;
	Elem* new_base = new Elem[new_size];

	// 复制元素
	for (size_t i = 0; i < _length; i++) {
		new_base[i] = _base[i];
	}

	// 释放原有内存
	delete[] _base;

	// 取代
	_size = new_size;
	_base = new_base;
}

template <typename Elem, size_t INCREAMENT>
size_t Array<Elem, INCREAMENT>::Length() {
	return _length;
}

/**
 * 插入元素
 * 动态分配大小
 */
template <typename Elem, size_t INCREAMENT>
Status Array<Elem, INCREAMENT>::Insert(const Elem e) {

	// 扩充数组大小
	if (_length == _size) Expand();

	_base[_length] = e;
	_length++;
	return OK;
}


/**
 * 删除末尾元素
 * 动态分配大小
 */
template <typename Elem, size_t INCREAMENT>
Status Array<Elem, INCREAMENT>::Delete(Elem& e) {
	// 为空的情况
	if (_length == 0) return ERROR;

	e = _base[--_length];

	// 动态分配大小
	if (_length <= (_size - INCREAMENT)) {
		Elem* new_base = new Elem[_size - INCREAMENT];
		for (size_t i = 0; i < _length; i++) {
			new_base[i] = _base[i];
		}
		delete[] _base;
		_base = new_base;
		_size -= INCREAMENT;
	}

	return OK;
}


/**
 * 数组访问运算符重载
 * 可以处理引用超界的情况
 */
template <typename Elem, size_t INCREAMENT>
Elem& Array<Elem, INCREAMENT>::operator[](const size_t index) {
	if (index < _length)
		return _base[index];
	else
		throw(1);
}

/**
 * 手动增加数组的长度
 */
template <typename Elem, size_t INCREAMENT>
Status Array<Elem, INCREAMENT>::Resize(size_t length) {
	if (length <= _length) return ERROR;
	else if (length <= _size) _length = length;
	else {
		Elem* new_base = new Elem[length];
		for (size_t i = 0; i < _length; i++) {
			new_base[i] = _base[i];
		}
		delete[] _base;
		_base = new_base;
		_length = length;
		_size = length;
	}
}
