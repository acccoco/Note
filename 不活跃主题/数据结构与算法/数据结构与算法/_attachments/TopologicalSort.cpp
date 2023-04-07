#include <vector>
#include <stack>
using namespace std;

// 拓扑排序
vector<int> TopologicalSort(Graph graph) {
	// 初始化栈，存放入度为0的结点
	stack<int> stack;
	for (auto vertex: graph) {
		if (vertex.inDegree == 0) {
			stack.push(vertex);
		}
	}
	
	while(!stack.empty()) {
		// 弹出结点，并输出
		Vertex vertex = stack.pop();
		result.push_back(vertex);
		
		// 修改后序结点的入度，并将入度为0的结点压入栈
		for (auto laterVertex: vertex.after) {
			laterVertex.inDegree--;
			if (laterVertex.inDegree == 0) {
				stack.push(laterVertex);
			}
		}
	}
	
	return result;
}
