/*
* 2018114686 ������ ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)

int n, m;
vector<vector<int>> graph;
vector<int> path;
int color = 1;
bool flag = false;

bool Promising(int depth) {
	for (int i = 1; i < depth; i++) {
		if (graph[i][depth] == 1 && path[i] == path[depth])
			return false;
	}

	return true;
}

//depth = ���������� ��ĥ�� vertex
void Solve(int depth) {
	if (!Promising(depth)) return;
	if (flag) return;

	if (depth == n) flag = true;
	else {
		for (int i = 0; i < color; i++) {
			path.at(depth + 1) = i;
			Solve(depth + 1);
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n >> m;
	graph.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		vector<int> arr(n + 1, 0);
		graph[i] = arr;
	}

	for (int i = 1; i <= m; i++) {
		int s, e;
		cin >> s >> e;
		graph[s][e] = 1;
		graph[e][s] = 1;
	}

	for (color = 1; color < 5; color++) {
		path.clear();
		path.resize(n + 1);
		Solve(0);
		if (flag) break;
	}

	cout << color;
	
	return 0;
}