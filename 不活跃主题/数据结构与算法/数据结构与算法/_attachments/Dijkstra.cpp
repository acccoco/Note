#include <vector>
#include <stack>
#include <iostream>
using namespace std;


// 边的数据结构
struct Arc {
	int length;
	int destinyVertex;
	Arc(int length, int destinyVertex) : length(length), destinyVertex(destinyVertex) {}
};

vector<vector<int>> Dijkstra(vector<vector<Arc>>& graph) {
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
			if (!solved[arc.destinyVertex] && distance[toSolveVertex] + arc.length < distance[arc.destinyVertex]) {
				distance[arc.destinyVertex] = distance[toSolveVertex] + arc.length;
				path[arc.destinyVertex] = toSolveVertex;
			}
		}
	}

	// 输出最短路径
	auto shortestPath = vector<vector<int>>(vertexNumbers);
	for (int vertexID = 0; vertexID < vertexNumbers; vertexID++) {
		
		// 将路径读入栈
		stack<int> pathChain;
		int arcNumbers = 0;
		int parentVertex = path[vertexID];
		while (parentVertex != -1) {
			pathChain.push(parentVertex);
			parentVertex = path[parentVertex];
			arcNumbers++;
		}
		// 从栈中输出路径
		for (int i = 0; i < arcNumbers; i++) {
			shortestPath[vertexID].push_back(pathChain.top());
			pathChain.pop();
		}
	}

	return shortestPath;
}

/**
 * 测试部分
 */

void main() {
	vector<vector<Arc>> graph = { {Arc(10, 1), Arc(5, 4)}, {Arc(1, 2), Arc(2, 4) }, {Arc(4, 3)}, {Arc(6, 2), Arc(7, 0)}, {Arc(3, 1), Arc(9, 2), Arc(2, 3)} };
	auto tree = Dijkstra(graph);
	for (auto vertexs : tree) {
		for (auto vertex : vertexs) {
			cout << vertex << " ";
		}
		cout << endl;
	}
}