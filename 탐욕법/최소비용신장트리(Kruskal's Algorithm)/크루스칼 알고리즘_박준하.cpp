/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include <algorithm>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)
const int MAX = 20;

class Edge {
public:
	int s, e, w;

	Edge() {}
	Edge(int _s, int _e, int _w) {
		s = _s; e = _e; w = _w;
	}
};

class UnionFind {
public:
	vector<int> parent;

	UnionFind(int num) {
		parent.reserve(num);
		for (int i = 0; i < num; i++)
			parent.push_back(i);
	}

	void Merge(int a, int b) {
		int parentA = Find(a);
		int parentB = Find(b);
		
		if (parentA == parentB) return;
		parent[parentA] = parentB;
	}

	int Find(int a) {
		if (parent[a] == a) return a;

		int theParent = Find(parent[a]);
		parent[a] = theParent;
		return theParent;
	}

	bool equal(int a, int b) {
		return Find(a) == Find(b);
	}
};

int n, m;
vector<Edge> edges;
vector<Edge> F;

bool compare(const Edge& A, const Edge& B) {
	return (A.w < B.w);
}

void Solve() {
	UnionFind uf(n+1);
	vector<Edge>::iterator iter = edges.begin();

	while (F.size() < n - 1) {
		Edge tmp = *(iter++);
		if (uf.equal(tmp.s, tmp.e)) continue;
		
		F.push_back(tmp);
		uf.Merge(tmp.s, tmp.e);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d %d", &n, &m);
	FOR(i, m) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		edges.push_back(Edge(s, e, w));
	}
	sort(edges.begin(), edges.end(), compare);
	
	Solve();
	for (auto it : F) {
		printf("%d %d %d\n", it.s, it.e, it.w);
	}

	return 0;
}