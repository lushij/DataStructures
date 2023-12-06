#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include<vector>
#include <algorithm>
using namespace std;
/* 基于邻接矩阵实现的无向图类 */
class GraphAdjMat {
	vector<int> vertices; // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
	vector<vector<int>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”
	//相当于二维数组
public:
	/* 构造方法 */
	GraphAdjMat(const vector<int>& vertices, const vector<vector<int>>& edges) {
		// 添加顶点
		for (int val : vertices) {
			addVertex(val);
		}
		// 添加边
		// 请注意， edges 元素代表顶点索引，即对应 vertices 元素索引
		for (const vector<int>& edge : edges) {
			addEdge(edge[0], edge[1]);
		}
	}
	/* 获取顶点数量 */
	int size() const {
		return vertices.size();
	}
	/* 添加顶点 */
	void addVertex(int val) {
		int n = size();
		// 向顶点列表中添加新顶点的值
		vertices.push_back(val);
		// 在邻接矩阵中添加一行
		adjMat.emplace_back(vector<int>(n, 0));
		// 在邻接矩阵中添加一列
		for (vector<int>& row : adjMat) {
			row.push_back(0);
		}
	}
	/* 删除顶点 */
	void removeVertex(int index) {
		if (index >= size()) {
			throw out_of_range(" 顶点不存在 ");
		}
		// 在顶点列表中移除索引 index 的顶点
		vertices.erase(vertices.begin() + index);
		// 在邻接矩阵中删除索引 index 的行
		adjMat.erase(adjMat.begin() + index);
		// 在邻接矩阵中删除索引 index 的列
		for (vector<int>& row : adjMat) {
			row.erase(row.begin() + index);
		}
	}
	/* 添加边 */
	// 参数 i, j 对应 vertices 元素索引
	void addEdge(int i, int j) {
		// 索引越界与相等处理
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
			throw out_of_range(" 顶点不存在 ");
		}
		// 在无向图中，邻接矩阵沿主对角线对称，即满足 (i, j) == (j, i)
		adjMat[i][j] = 1;
		adjMat[j][i] = 1;
	}
	/* 删除边 */
	// 参数 i, j 对应 vertices 元素索引
	void removeEdge(int i, int j) {
		// 索引越界与相等处理
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j) {
			throw out_of_range(" 顶点不存在 ");
		}
		adjMat[i][j] = 0;
		adjMat[j][i] = 0;
	}

	template <typename T>
	void printVector(const vector<T>& vec) {
		cout << "[ ";
		for (const auto& element : vec) {
			cout << element << " ";
		}
		cout << "]" << endl;
	}

	template <typename T>
	void printVectorMatrix(const vector<vector<T>>& mat) {
		for (const auto& row : mat) {
			cout << "[ ";
			for (const auto& element : row) {
				cout << element << " ";
			}
			cout << "]" << endl;
		}
	}
	/* 打印邻接矩阵 */
	void print() {
		cout << " 顶点列表 = ";
		printVector(vertices);
		cout << " 邻接矩阵 =" << endl;
		printVectorMatrix(adjMat);
	}
	/* 深度优先搜索 */
	void dfs(int startVertex) {
		// 使用一个辅助数组来标记顶点是否被访问过
		vector<bool> visited(size(), false);

		// 调用实际的 DFS 函数
		dfsRecursive(startVertex, visited);
	}
private:
		/* 递归的深度优先搜索 */
		void dfsRecursive(int vertex, vector<bool>& visited) {
			// 访问当前顶点
			cout << vertices[vertex] << " ";
			visited[vertex] = true;

			// 对当前顶点的所有邻居进行递归调用
			for (int i = 0; i < size(); ++i) {
				if (adjMat[vertex][i] == 1 && !visited[i]) {
					dfsRecursive(i, visited);
				}
			}
		}
};
int main()
{
	// 创建顶点列表和边列表
	vector<int> vertices = { 0, 1, 2, 3 };
	vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 0} };
	// 创建图的实例
	GraphAdjMat myGraph(vertices, edges);
	// 执行一些图操作
	myGraph.addVertex(4);
	myGraph.addVertex(5);
	myGraph.addEdge(1, 4);
	myGraph.addEdge(1, 5);
	// 打印图的信息
	myGraph.print();
	// 执行深度优先搜索
	cout << "深度优先搜索结果: ";
	myGraph.dfs(0);
	return 0;
}