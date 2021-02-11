#include <iostream>
#include <vector>
#include <limits>
#include <Windows.h>

using namespace std;

vector<vector<int>> Prima
// матрица смежности, значение бессконечности
(const vector<vector<int>>& g, const int &infinity)
{
	int n = g.size();

	vector<vector<int>> result(n, vector<int>(n, 0));

	// включена вершина в дерево или нет
	vector<bool> used(n);

	// хранит вес наименьшего допустимого ребра из вершины
	vector<int> min_e(n, infinity),
	// содержит конец этого наименьшего ребра 
		sel_e(n, -1);
	min_e[0] = 0;

	for (int i = 0; i < n; ++i)
	{
		int v = -1;
		// находим не использованную минимальную
		for (int j = 0; j < n; ++j)
		{
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
			{
				v = j;
			}
		}

		if (min_e[v] == infinity)
		{
			cout << "No MST!";
			exit(0);
		}

		used[v] = true;
		if (sel_e[v] != -1)
		{
			// cout << v << " " << sel_e[v] << endl;
			result[v][sel_e[v]] = g[v][sel_e[v]];
			result[sel_e[v]][v] = g[sel_e[v]][v];
		}

		for (int to = 0; to < n; ++to)
		{
			if (g[v][to] < min_e[to] && g[v][to])
			{
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
		}
	}

	return result;
}

vector<int> Dijkstra
// матрица смежности, вершина от которой нужно найти минимальные пути ко всем остальным
(const vector<vector<int>>& matrix, const int& s, const int& infinity)
{
	int size = matrix.size();

	vector<int> weight(size, infinity);
	vector<bool> valid(size, true);
	weight[s] = 0;

	for (int i = 0; i < size; ++i)
	{
		int min_weight = infinity;
		int ID_min_weight = -1;

		for (int j = 0; j < size; ++j)
		{
			if (valid[j] && weight[j] < min_weight)
			{
				min_weight = weight[j];
				ID_min_weight = j;
			}
		}

		for (int j = 0; j < size; ++j)
		{
			if (weight[ID_min_weight] + matrix[ID_min_weight][j] < weight[j] && matrix[ID_min_weight][j])
			{
				weight[j] = weight[ID_min_weight] + matrix[ID_min_weight][j];
			}
		}
		valid[ID_min_weight] = false;
	}


	return weight;
}

int maxInMatrix(const vector<vector<int>>& g)
{
	int max = g[0][0];

	int rowSize = g.size(),
		colSize = g[0].size();

	for (int i = 0; i < rowSize; ++i)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (max < g[i][j])
			{
				max = g[i][j];
			}
		}
	}

	return max;
}

void dfs(const vector<vector<int>>& graph, vector<bool> &used, vector<int>& result, int node_index)
{
	used[node_index] = true;
	int n = graph.size();

	for (int i = 0; i < n; ++i)
	{
		if (graph[node_index][i] && !used[i])
		{
			result.push_back(i);
			dfs(graph, used, result, i);
		}
	}
}

vector<int> dfs(const vector<vector<int>>& graph, int node_index)
{
	int n = graph.size();
	vector<bool> used(n, false);
	vector<int> result;
	result.push_back(node_index);

	dfs(graph, used, result, node_index);

	return result;
}

vector<pair<int, int>> vertexDegree(const vector<vector<int>>& g)
{
	int n = g.size();

	vector<pair<int, int>> result(n, pair<int, int>(0, 0));

	for (int i = 0; i < n; ++i)
	{
		result[i].first = i;
		for (int j = 0; j < n; ++j)
		{
			if (g[i][j])
			{
				result[i].second++;
			}
		}
	}

	return result;
}

double average_vertex_degree(const vector<pair<int, int>>& g)
{
	double sum = 0;
	int n = g.size();

	for (int i = 0; i < n; ++i)
	{
		sum += g[i].second;
	}

	return sum / static_cast<double>(n);
}

void printMatrix(const vector<vector<int>>& g)
{
	int n = g.size();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << g[i][j] << ' ';
		}
		cout << '\n';
	}
}

void outVector(const vector<int>& v)
{
	int n = v.size();

	for (int i = 0; i < n; i++)
	{
		cout << v[i] << ' ';
	}
}

void print_pairs(const vector<pair<int, int>>& g)
{
	int n = g.size();

	for (int i = 0; i < n; ++i)
	{
		cout << g[i].first << ' ' << g[i].second << '\n';
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	// входные данные

	vector<vector<int>> adjacencyMatrix =
	{
{ 0, 5, 2, 7, 4, 8, 8, 8, 0, 6, 8, 4 },
{ 5, 0, 7, 2, 0, 8, 9, 6, 4, 2, 5, 4 },
{ 2, 7, 0, 1, 3, 3, 8, 3, 2, 6, 3, 6 },
{ 7, 2, 1, 0, 6, 8, 0, 6, 3, 9, 4, 3 },
{ 4, 0, 3, 6, 0, 9, 2, 3, 5, 9, 6, 8 },
{ 8, 8, 3, 8, 9, 0, 9, 5, 4, 6, 9, 1 },
{ 8, 9, 8, 0, 2, 9, 0, 0, 0, 5, 5, 8 },
{ 8, 6, 3, 6, 3, 5, 0, 0, 0, 7, 6, 3 },
{ 0, 4, 2, 3, 5, 4, 0, 0, 0, 6, 5, 4 },
{ 6, 2, 6, 9, 9, 6, 5, 7, 6, 0, 8, 1 },
{ 8, 5, 3, 4, 6, 9, 5, 6, 5, 8, 0, 9 },
{ 4, 4, 6, 3, 8, 1, 8, 3, 4, 1, 9, 0 },
	};

	cout << "Исходный граф:\n";
	printMatrix(adjacencyMatrix);

	// матрица смежности остова
	vector<vector<int>> O = Prima(adjacencyMatrix, maxInMatrix(adjacencyMatrix) + 1);

	cout << "Мимнимальный остов:\n";
	printMatrix(O);

	int v;
	cout << "Введите вершину с которой нужно начать поиск в глубину: ";
	cin >> v;
	cout << "Поиск в глубину в остове:\n";
	outVector(dfs(O, v));
	cout << '\n';

	cout << "Введите вершину от которой нужно найти расстояние до всех остальных: ";
	cin >> v;
	cout << "Расстояние от " << v << "-й вершины до всех остальных:\n";
	outVector(Dijkstra(adjacencyMatrix, v, maxInMatrix(adjacencyMatrix) + 1));
	cout << '\n';

	// вектор (вершина, cтепень)
	vector<pair<int, int>> ostovVertexDegree = vertexDegree(O);
	cout << "Степени вершин остова(вершина, степень):\n";
	print_pairs(ostovVertexDegree);

	cout << "Средняя степень вершин остова(вершина, степень): " << average_vertex_degree(ostovVertexDegree) << '\n';

	return 0;
}