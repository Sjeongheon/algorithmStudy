/*
* 2018114686 ������ ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF 123456789
#define MAX 10

struct Node {
	vector<int> path;
	int length;
	int level;
	int bound;
};

class CompareNode {
public:
	bool operator()(Node* a, Node* b) {
		return a->bound > b->bound;
	}
};

int n, m;
int graph[MAX][MAX];
priority_queue<Node*, vector<Node*>, CompareNode> pq;
int cnt = 0;
Node minPath;

bool DoesContain(const vector<int>& p, int v) {
	for (int i : p) {
		if (v == i) return true;
	}
	return false;
}

bool HasIncoming(const vector<int>& p, int v) {
	for (auto it = p.begin()+1; it != p.end(); it++) {
		if (*it == v) return true;
	}
	return false;
}

bool hasOutGoing(const vector<int>& p, int v) {
	for (auto it = p.begin(); it != p.end()-1; it++) {
		if (*it == v) return true;
	}
	return false;
}

int RemainingVertex(const vector<int>& p) {
	vector<int> checkarr(n+1, 0);
	for (int i : p) {
		checkarr[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (checkarr[i] == 0) return i;
	}
	return -1;
}

int CalcBound(const vector<int>& p, int len) {
	int result = len;
	//outGoing�� ���� ��� ���� ��ȸ
	for (int i = 1; i <= n; i++) {
		if (hasOutGoing(p, i)) continue;
		int minval = INF;
		//p�� �ִ� �������� ���ư��� �ʴ� ��� ���� ��ȸ
		for (int j = 1; j <= n; j++) {
			//�ڱ��ڽ����� ���ư��� ��� ����
			if (i == j) continue;
			//1�δ� ���ư� �� ���� ���̽� ����
			if (j == 1 && i == p.back()) continue;
			//1���� �湮�ߴ� ���� ���ư��� ���̽� ����
			if (HasIncoming(p, j)) continue;

			if (graph[i][j] != INF) {
				minval = min(minval, graph[i][j]);
			}
		}
		result += minval;
	}

	return result;
}

Node* MakeNode(vector<int> p, int len, int level) {
	Node* newNode = new Node();
	newNode->path = p;
	newNode->length = len;
	newNode->level = level;
	newNode->bound = CalcBound(p, len);

	return newNode;
}

void Solve() {
	vector<int> rootp;
	rootp.push_back(1);
	pq.push(MakeNode(rootp, 0, 0));
	cnt++;

	while (!pq.empty()) {
		Node* curNode = pq.top(); pq.pop();

		if (curNode->bound >= minPath.length) {
			delete(curNode);
			continue;
		}

		vector<int> newpath = curNode->path;
		//�̹� �湮�߰ų� ���� ���� ������ ������ ��� ���� ��ȸ
		for (int i = 2; i <= n; i++) {
			if (DoesContain(curNode->path, i) ||
				graph[curNode->path.back()][i] == INF)
				continue;

			//������� ����
			newpath.push_back(i);
			Node* tmp = MakeNode(newpath,
				curNode->length + graph[curNode->path.back()][i],
				curNode->level+1);
			newpath.pop_back();

			//�湮�� vertex�� �ϳ� ���Ҵٸ�
			if (tmp->level >= n-2) {
				//last vertex
				int lastv = RemainingVertex(tmp->path);
				//last vertex�� �� �� �ֳ� => path�� �߰�
				if (graph[tmp->path.back()][lastv] != INF) {
					tmp->length += graph[tmp->path.back()][lastv];
					tmp->path.push_back(lastv);

					//1�� ���ư� �� �ֳ� => path�� 1�߰�
					if (graph[tmp->path.back()][1] != INF) {
						tmp->length += graph[tmp->path.back()][1];
						tmp->path.push_back(1);
					}
					//min length Ȯ�� �� ������Ʈ
					if (tmp->length < minPath.length) {
						minPath.length = tmp->length;
						minPath.path = tmp->path;
					}
				}
				delete(tmp);
			}
			else {
				if (tmp->bound < minPath.length) {
					pq.push(tmp); cnt++;
				}
			}
		}

		delete(curNode);

		int* pint = new int;
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	FOR(i, MAX) {
		FOR(j, MAX) {
			graph[i][j] = INF;
			if (i == j)
				graph[i][j] = 0;
		}
	}

	cin >> n >> m;
	FOR(i, m) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u][v] = w;
	}

	minPath.length = INF;
	Solve();
	for (int i = 0; i < minPath.path.size(); i++) {
		printf("%d", minPath.path[i]);
		if (i != minPath.path.size() - 1)
			printf(" ");
	}
	printf("\n");
	printf("%d %d", minPath.length, cnt);

	return 0;
}