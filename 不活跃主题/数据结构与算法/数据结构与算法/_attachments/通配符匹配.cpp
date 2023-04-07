// 通配符匹配	
#include <assert.h>
#include <vector>
#include <string>
using std::vector;
using std::string;


class Solution {
public:
	bool isMatch(string s, string p) {
		int lengthS = s.size();
		int lengthP = p.size();

		//
		// 排除s为空串或p为空串的特殊情况
		if (lengthS == 0) {
		// 1. 字符串s为空串，模式串p也为空串
			if (lengthP == 0) {
				return true;
			}
		// 2. 字符串s为空串，模式串p不为空串
			else {
				for (auto c : p) {
					if (c != '*') {
						return false;
					}
				}
				return true;
			}
		}
		// 3. 模式串p为空串，但字符串不为空串
		if (lengthP == 0)
			return false;

		//
		// 初始化第一列，表示 p[0...i] 是否能够匹配 空串
		vector<char> col0 = vector<char>(lengthP);
		col0[0] = p[0] == '*' ? 1 : 0;
		for (int i = 1; i < lengthP; ++i) {
			col0[i] = p[i] == '*' ? col0[i - 1] : 0;
		}

		//
		// 初始化第一行
		vector<char>* rowCurrent = new vector<char>(lengthS + 1);
		vector<char>* rowPrevious = new vector<char>(lengthS + 1);
		// 第0位
		(*rowCurrent)[0] = col0[0];
		// 第1位
		if (p[0] == '*' || p[0] == '?' || p[0] == s[0]) {
			(*rowCurrent)[1] = 1;
		}
		else {
			(*rowCurrent)[1] = 0;
		}
		// 后续位
		if (p[0] == '*') {
			for (int j = 2; j <= lengthS; ++j) {
				(*rowCurrent)[j] = 1;
			}
		}
		else {
			for (int j = 2; j <= lengthS; ++j) {
				(*rowCurrent)[j] = 0;
			}
		}

		//
		// 完善整个dp
		vector<char>* temp;
		for (int i = 1; i < lengthP; ++i) {
			// 交换指针
			temp = rowCurrent;
			rowCurrent = rowPrevious;
			rowPrevious = temp;
			// 填充第一个位置
			(*rowCurrent)[0] = col0[i];

			for (int j = 1; j <= lengthS; ++j) {
				// 1. p[i]是?或者p[i]==s[j]的情况
				if (p[i] == '?' || p[i] == s[j - 1]) {
					(*rowCurrent)[j] = (*rowPrevious)[j - 1];
				}
				// 2. p[i]是*的情况
				else if (p[i] == '*') {
					(*rowCurrent)[j] = (*rowPrevious)[j] || (*rowPrevious)[j - 1] || (*rowCurrent)[j - 1];
				}
				// 3. p[i]!=s[j]
				else {
					(*rowCurrent)[j] = 0;
				}
			}
		}

		return (*rowCurrent)[lengthS];
	}
};

int main() {
	Solution s = Solution();
	assert(s.isMatch("adceb", "*a*b") == true);
	assert(s.isMatch("a", "a*") == true);
	assert(s.isMatch("mississippi", "m??*ss*?i*pi") == false);
	assert(s.isMatch("aa", "a") == false);
	assert(s.isMatch("aa", "*") == true);
	assert(s.isMatch("cb", "?a") == false);
	assert(s.isMatch("acdcb", "a*c?b") == false);
}