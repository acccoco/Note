#include <vector>


struct Heap {
	typedef int HeapElement;
	typedef bool (*CompareFunction)(HeapElement*, HeapElement*);

	std::vector<HeapElement*> heapVector;

	// 用AdjustDown的方法来初始化
	void InitHeap_1(std::vector<HeapElement>& source, CompareFunction Compare) {
		int heapSize = source.size();
		heapVector.resize(heapSize);

		for (int i = 0; i < heapSize; i++) {
			heapVector[i] = &(source[i]);
		}

		for (int i = heapSize / 2 - 1; i >= 0; i--) {
			AdjustDown(i, Compare);
		}
	}
	// 用AdjustUp的方法来初始化
	void InitHeap_2(std::vector<HeapElement>& source, CompareFunction Compare) {
		int heapSize = source.size();
		heapVector.resize(heapSize);

		for (int i = 0; i < heapSize; i++) {
			heapVector[i] = &(source[i]);
		}

		for (int i = 0; i < heapSize; i++) {
			AdjustUp(i, Compare);
		}
	}

	void AdjustDown(int nodeOrdinal, CompareFunction Compare) {
		int heapSize = heapVector.size();
		HeapElement* nodeElement = heapVector[nodeOrdinal];

		while (nodeOrdinal < heapSize) {
			int leftChildOrdinal = nodeOrdinal * 2 + 1;
			int rightChildOrdinal = leftChildOrdinal + 1;

			// 没有子
			if (leftChildOrdinal >= heapSize) {
				break;
			}
			// 只有左子
			else if (rightChildOrdinal >= heapSize) {
				if (Compare(heapVector[leftChildOrdinal], nodeElement)) {
					heapVector[nodeOrdinal] = heapVector[leftChildOrdinal];
					nodeOrdinal = leftChildOrdinal;
				}
				break;
			}
			// 有双子
			else {
				int betterChildOrdinal = Compare(heapVector[leftChildOrdinal], heapVector[rightChildOrdinal]) ? leftChildOrdinal : rightChildOrdinal;
				if (Compare(heapVector[betterChildOrdinal], nodeElement)) {
					heapVector[nodeOrdinal] = heapVector[betterChildOrdinal];
					nodeOrdinal = betterChildOrdinal;
				}
				else {
					break;
				}
			}
		}

		heapVector[nodeOrdinal] = nodeElement;
	}

	void AdjustUp(int nodeOrdinal, CompareFunction Compare) {
		int heapSize = heapVector.size();
		HeapElement* nodeElement = heapVector[nodeOrdinal];

		while (nodeOrdinal > 0) {
			int parentOrdinal = (nodeOrdinal - 1) / 2;

			if (Compare(nodeElement, heapVector[parentOrdinal])) {
				heapVector[nodeOrdinal] = heapVector[parentOrdinal];
				nodeOrdinal = parentOrdinal;
			}
			else {
				break;
			}
		}

		heapVector[nodeOrdinal] = nodeElement;
	}
};





// 测试部分

#include <iostream>
void __HeapTest__() {
	auto Compare = [](int* a, int* b) {
		return *a < *b ? true : false;
	};

	// 原始数组
	std::vector<int> source = { 2, 3, 4, 6, 7, 89, 456, 73, 1, 0 };
	std::cout << "数组初始状态: " << std::endl;
	for (auto i : source) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	// 第一种建堆方式
	std::cout << "AdjustDown建堆：" << std::endl;
	Heap h_1;
	h_1.InitHeap_1(source, (Heap::CompareFunction)Compare);
	for (int i = 0; i < h_1.heapVector.size(); i++) {
		std::cout << *(h_1.heapVector[i]) << " ";
	}
	std::cout << std::endl;

	// 第二种建堆方式
	std::cout << "AdjustUp建堆：" << std::endl;
	Heap h_2;
	h_2.InitHeap_2(source, (Heap::CompareFunction)Compare);
	for (int i = 0; i < h_2.heapVector.size(); i++) {
		std::cout << *(h_2.heapVector[i]) << " ";
	}
	std::cout << std::endl;
}