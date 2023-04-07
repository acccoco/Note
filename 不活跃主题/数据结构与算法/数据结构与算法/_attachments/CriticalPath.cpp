#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 邻接表的组成
struct Vertex {
	int data;
	Edge* firstEdge;
};
struct Edge {
	int destinyVertex;
	int weight;
	Edge* nextEdge;
};
void TopologicalSort(const vector<Vertex>& graph, vector<int>& sortSequence);
/**
* 求解关键路径
*	图：邻接表
*	ve[]：顶点的最早开始时间
*	vl[]：顶点的最迟开始时间
*	ee：边的最早开始时间
*	el：边的最迟开始时间
*/
void CriticalPath(const vector<Vertex>& graph) {
	int vertexNumber = graph.size();

	// 获得拓扑排序的序列
	vector<int> sortSequence;
	TopologicalSort(graph, sortSequence);

	// 使用拓扑序列，求解ve[]
	vector<int> ve = vector<int>(vertexNumber, 0);
	for (int vertex : sortSequence) {
		for (Edge* edge = graph[vertex].firstEdge; edge; edge = edge->nextEdge) {
			int destinyVertex = edge->destinyVertex;
			if (ve[destinyVertex] < ve[edge] + edge->weight) {
				ve[destinyVertex] = ve[edge] + edge->weight;
			}
		}
	}

	// 使用拓扑逆序列，求解vl[]
	vector<int> vl = vector<int>(vertexNumber, ve[vertexNumber - 1]);
	for (int i = vertexNumber - 1; i >= 0; i--) {
		int vertex = sortSequence[i];
		for (Edge* edge = graph[vertex].firstEdge; edge; edge = edge->nextEdge) {
			int destinyVertex = edge->destinyVertex;
			if (vl[vertex] > vl[destinyVertex] - edge->weight) {
				vl[vertex] = vl[destinyVertex] - edge->weight;
			}
		}
	}

	// 求解ee[]和el[]
	for (int vertex = 0; vertex < vertexNumber; vertex++) {
		for (Edge* edge = graph[vertex].firstEdge; edge; edge = edge->nextEdge) {
			int destinyEdge = edge->destinyVertex;
			int ee = ve[vertex];
			int el = vl[destinyEdge] - edge->weight;

			// 判断是否是关键路径
			if (ee == el) {
				cout << "顶点" << vertex << "的边" << edge << "是关键路径" << endl;
			}
		}
	}
}