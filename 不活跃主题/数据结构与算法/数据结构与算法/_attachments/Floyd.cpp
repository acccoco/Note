#include <iostream>
#include <vector>
using namespace std;


/**
* 数据结构
*	图使用邻接矩阵存储：graph[i][j]
*	两点之间的距离使用 distance[i][j] 来表示
*	两点之间的路径使用 path[i][j][k] 来表示，为true，意味着k在i-j之间的路径上
* Floyd算法的关键步骤在于：distance[i][j] < distance[i][k] + distance[k][j]
*/
void Floyd(vector<vector<int>> graph, vector<vector<int>> distance, vector<vector<vector<int>>> path) {
	int vertexNumber = graph.size();
	// 初始化distance[i][j]和path[i][j][]
	for (int i = 0; i < vertexNumber; i++) {
		for (int j = 0; j < vertexNumber; j++) {
			distance[i][j] = graph[i][j];	// 初始化distance[][][]

			for (int k = 0; k < vertexNumber; k++) {	// 初始化path[][]
				path[i][j][k] = false;
			}
			if (distance[i][j] < INT32_MAX) {
				path[i][j][i] = path[i][j][j] = true;
			}
		}
	}

	// 进行Floyd算法的迭代
	for (int k = 0; k < vertexNumber; k++) {
		for (int i = 0; i < vertexNumber; i++) {
			for (int j = 0; j < vertexNumber; j++) {

				// 更新distance[i][j]
				if (distance[i][j] > distance[i][k] + distance[k][j]) {
					distance[i][j] = distance[i][k] + distance[k][j];

					// 更新path[i][j][]
					for (int mid = 0; mid < vertexNumber; mid++) {
						path[i][j][mid] = path[i][k][mid] || path[k][j][mid];
					}
				}
			}
		}
	}
}