/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)
const int MAX = 20;
const int INF = 1234567890;

class Edge {
public:
	int s, e, w;

	Edge() {}
	Edge(int _s, int _e, int _w) {
		s = _s; e = _e; w = _w;
	}
};

int n, m;
int W[MAX][MAX];
vector<Edge> F;
int nearest[MAX];
int dist[MAX];

void Solve() {
	//N(F) = n-1이 될때까지 반복
	while(F.size() < n-1){
		//현재 solution set에서 가장 가까운 v 선택
		int min = INF;
		int nearv = 0;
		for (int i = 2; i <= n; i++) {
			if (min > dist[i] && dist[i] >= 0) {
				min = dist[i];
				nearv = i;
			}
		}

		//v와 nearest[v] 를 잇는 edge 추가 후 dist[v] = -1로 변경
		int s = nearv;
		int e = nearest[nearv];
		F.push_back(Edge(s, e, W[s][e]));
		dist[nearv] = -1;

		//모든 노드를 순회하며 원래의 dist와 v와의 거리중 짧은 것 선택
		for (int i = 2; i <= n; i++) {
			if (dist[i] > W[i][nearv]) {
				dist[i] = W[i][nearv];
				nearest[i] = nearv;
			}
		}

		//현재 상태 출력
		for (int i = 2; i <= n; i++) {
			printf("%d", nearest[i]);
			if (i != n) printf(" ");
		}
		printf("\n");
		for (int i = 2; i <= n; i++) {
			if (dist[i] == INF) printf("INF");
			else printf("%d", dist[i]);

			if (i != n) printf(" ");
		}
		printf("\n");
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	FOR(i, MAX) {
		FOR(j, MAX) W[i][j] = INF;
	}

	scanf("%d %d", &n, &m);
	FOR(i, m) {
		int s, e, w;
		scanf("%d %d %d", &s, &e, &w);
		W[s][e] = W[e][s] = w;
	}

	//초기화
	for (int i = 1; i <= n; i++) {
		nearest[i] = 1;
		dist[i] = W[1][i];
	}
	dist[1] = -1;

	Solve();

	for (auto it : F) {
		printf("%d %d %d\n", it.s, it.e, it.w);
	}

	return 0;
}