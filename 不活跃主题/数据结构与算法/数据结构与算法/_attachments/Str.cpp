#include "Str.h"
using namespace std;

#pragma region 基本函数
/**
 * 这个类很关键，容器类会调用
 */
Str::Str() {
	_base = NULL;
	_length = 0;
	_mm_size = 0;
}
Str::Str(const char* str) {
	// 分配内存
	_base = (char*)malloc(INIT_LENGTH * sizeof(char));
	if (!_base) throw(0);
	_mm_size = INIT_LENGTH;

	// 复制内容
	int i = 0; char c = str[0];
	while (c != '\0') {
		_base[i] = c;
		i++; c = str[i];
		if (i == _mm_size) {
			char* temp = (char*)realloc(_base, (_mm_size + INCREMENT) * sizeof(char));
			if (!temp) throw(0);
			_base = temp;
			_mm_size += INCREMENT;
		}
	}
	_base[i] = '\0';
	_length = i;
}
Str::~Str() {
	free(_base);
}
Str::Str(const Str& str) {
	_length = str._length;
	_mm_size = str._mm_size;
	_base = (char*)malloc(_mm_size * sizeof(char));
	if (!_base) throw(0);
	for (int i = 0; i <= _length; i++) {
		_base[i] = str._base[i];
	}
}
Str::Str(Str&& str) noexcept {
	_length = str._length;
	_mm_size = str._mm_size;
	_base = str._base;
	str._base = NULL;
}
void Str::operator=(const Str& str) {
	// 释放原来的内存
	free(_base);
	
	// 复制新的内容
	_length = str._length;
	_mm_size = str._mm_size;
	_base = (char*)malloc(_mm_size * sizeof(char));
	if (!_base) throw(0);
	for (int i = 0; i <= _length; i++) {
		_base[i] = str._base[i];
	}
}
void Str::operator=(Str&& str) noexcept {
	// 释放原来的内存
	free(_base);

	// 复制新的内容
	_length = str._length;
	_mm_size = str._mm_size;
	_base = str._base;
	str._base = NULL;
}
#pragma endregion








/**
 * 获得串的长度
 */
int Str::Length() {
	return _length;
}

/**
 * 将两个串连接为一个新串
 */
Str Str::Concat(Str& s1, Str& s2) {

	int len1 = s1._length;
	int len2 = s2._length;

	// 计算尺寸以及分配内存
	auto str = Str();
	str._length = len1 + len2;
	if (str._length < INIT_LENGTH) str._mm_size = INIT_LENGTH;
	else str._mm_size = INIT_LENGTH + (str._length - INIT_LENGTH + INCREMENT) / INCREMENT * INCREMENT;
	str._base = (char*)malloc(str._mm_size * sizeof(char));
	if (!str._base) throw(0);

	// 复制内容
	for (int i = 0; i < len1; i++) str._base[i] = s1._base[i];
	char* s2_start = str._base + len1;
	for (int i = 0; i < len2; i++) s2_start[i] = s2._base[i];

	return str;
}

/**
 * 判断是否为空串
 */
Bool Str::IsEmpty() {
	return _length == 0 ? TRUE : FALSE;
}

/**
 * 子串操作
 */
Str Str::SubString(int position, int len) {

	// 输入参数是否合法
	if (position < 0 || position + len > _length) throw(0);

	// 确定子串占用的内存长度
	int mm_size = INIT_LENGTH;
	if (len + 1 > INIT_LENGTH) {
		mm_size += (len - INIT_LENGTH + INCREMENT) / INCREMENT * INCREMENT;
	}
	char* str = (char*)malloc(mm_size * sizeof(char));
	if (!str) throw(0);

	// 进行内存复制
	char* start = _base + position;
	for (int i = 0; i < len; i++) {
		str[i] = start[i];
	}
	str[len] = '\0';


	// 将以上内容赋值给空对象
	Str sub = Str();
	sub._base = str;
	sub._mm_size = mm_size;
	sub._length = len;
	return sub;
}

/**
 * 标准输出的适配
 */
std::ostream& operator<<(std::ostream& out, const Str& str) {
	std::cout << str._base;
	return out;
}

/**
 * 比较两个串是否相等
 */
Bool Str::operator==(const Str& str2) {
	if (_length != str2._length) return FALSE;
	for (int i = 0; i < _length; i++) {
		if (_base[i] != str2._base[i]) return FALSE;
	}
	return TRUE;
}


/**
 * 模式串匹配，直接方法
 */
Status Str::pattern_direct(const Str& p, int pos, int& result) {
	if (pos + p._length > _length) return ERROR;

	int i = pos;
	int j = 0;

	while (i < _length && j < p._length) {
		if (_base[i] == p._base[j]) {
			i++;
			j++;
		}
		// 进行回溯
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	// 判断是否匹配成功
	if (j = p._length) {
		result = i - p._length;
		return OK;
	}
	else return ERROR;
}


/**
 * 计算模式字符串的next数组
 */
Status Str::Next(const Str& p, int* next) {
	next[0] = -1;
	int i = 0;
	int j = -1;
	while (i < p._length - 1) {
		if (j == -1 || p._base[i] == p._base[j]) {
			i++;
			j++;
			if (p._base[i] != p._base[j]) next[i] = j;
			else next[i] = j;
		}
		else {
			j = next[j];
		}
	}

	return OK;
}

/**
 * 匹配模式字符串的KMP算法
 */
Status Str::pattern_KMP(const Str& p, int pos, int& result) {
	if (pos + p._length > _length) return ERROR;

	// 计算模式串的next数组
	int* next = (int*)malloc(p._length * sizeof(int));
	if (!next) return ERROR;
	Next(p, next);

	// 进行匹配
	int i = pos;
	int j = 0;
	while (i < _length && j < p._length) {
		if (_base[i] == p._base[j]) {
			i++;
			j++;
		}
		// 仅j回溯，i不回溯
		else {
			j = next[j];
			if (j == -1) {
				i++;
				j++;
			}
		}
	}
	// 判断是否匹配成功
	if (j = p._length) {
		result = i - p._length;
		return OK;
	}
	else return ERROR;
}

