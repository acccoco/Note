#include <vector>
#include <iostream>
using namespace std;



// 边的数据结构
struct Arc {
	int length;
	int destinyVertex;
	Arc(int length, int destinyVertex) : length(length), destinyVertex(destinyVertex) {}
};
// 图使用的是邻接表实现，返回的树使用孩子表示法实现
vector<vector<int>> Prim(vector<vector<Arc>>& graph) {
	int vertexNumbers = graph.size();

	// 初始化辅助结构
	auto solved = vector<int>(vertexNumbers, 0);
	auto distance = vector<int>(vertexNumbers, INT32_MAX);
	auto path = vector<int>(vertexNumbers, -1);
	solved[0] = 1;
	for (auto arc : graph[0]) {
		distance[arc.destinyVertex] = arc.length;
		path[arc.destinyVertex] = 0;
	}

	// 只需要循环 n-1 次即可
	for (int i = 1; i < vertexNumbers; i++) {

		// 找到下一个结点
		int toSolveVertex = -1;
		int minDistance = INT32_MAX;
		for (int vertexID = 0; vertexID < vertexNumbers; vertexID++) {
			if (!solved[vertexID] && distance[vertexID] < minDistance) {
				toSolveVertex = vertexID;
				minDistance = distance[vertexID];
			}
		}

		// 更新辅助结构
		solved[toSolveVertex] = 1;
		for (auto arc : graph[toSolveVertex]) {
			if (!solved[arc.destinyVertex] && arc.length < distance[arc.destinyVertex]) {   // 注意此处的!solved
				distance[arc.destinyVertex] = arc.length;
				path[arc.destinyVertex] = toSolveVertex;
			}
		}
	}

	// 输出为孩子表示法的树
	auto tree = vector<vector<int>>(vertexNumbers);
	for (int vertexID = 1; vertexID < vertexNumbers; vertexID++) {  // 注意此处的1
		tree[path[vertexID]].push_back(vertexID);
	}
	return tree;
}

/**
 * 测试部分
 */

void main() {
	vector<vector<Arc>> graph = { {Arc(10, 1), Arc(5, 4)}, {Arc(1, 2), Arc(2, 4) }, {Arc(4, 3)}, {Arc(6, 2), Arc(7, 0)}, {Arc(3, 1), Arc(9, 2), Arc(2, 3)} };
	auto tree = Prim(graph);
	for (auto vertexs : tree) {
		for (auto vertex : vertexs) {
			cout << vertex << " ";
		}
		cout << endl;
	}
}