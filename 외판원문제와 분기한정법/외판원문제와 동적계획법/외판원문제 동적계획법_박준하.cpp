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

int n, m;
int rowCnt;
int graph[MAX][MAX];
int D[MAX][1 << (MAX - 1)];
int P[MAX][1 << (MAX - 1)];
int minidx = -1;

int countFlag(int num) {
	int cnt = 0;
	for (; num != 0; num >>= 1) {
		if (num & 1 == 1)
			cnt++;
	}
	return cnt;
}

bool doesContain(int S, int v) {
	return S & (1 << (v - 2));
}

void CalcSingleD(int v, int S) {
	int minval = INF;
	//S�� �����ϴ� ��� vertex��ȸ
	for (int i = 2; i <= n; i++) {
		if (!doesContain(S, i)) continue;
		int nextS = S & ~(1 << (i - 2));
		int tmp = graph[v][i] + D[i][nextS];
		if (minval > tmp) {
			minval = tmp;
			minidx = i;
		}
	}
	D[v][S] = minval;
	P[v][S] = minidx;
}

void PrintPath(int v, int S) {
	printf("%d ", v);
	//�����ڷῡ���� S == 1 �̶� ���ִµ� Ʋ������
	if (S == 0) {
		printf("1 ");
		return;
	}

	int nextv = P[v][S];
	int nexts = S & ~(1 << (nextv - 2));
	PrintPath(nextv, nexts);
}

void Solve() {
	for (int i = 2; i <= n; i++) {
		D[i][0] = graph[i][1];
	}
	//i : N(S)
	for (int i = 1; i < n-1; i++) {
		//��� row ��ȸ
		for (int S = 0; S < rowCnt; S++) {
			if (countFlag(S) != i) continue;
			//1�� ������ ��� vertex��ȸ
			for (int v = 2; v <= n; v++) {
				if (doesContain(S, v)) continue;
				//D[v][S]�� P[v][S] ���
				CalcSingleD(v, S);
			}
		}
	}

	//D[1][rowCnt-1] ���
	CalcSingleD(1, rowCnt - 1);
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	memset(P, 0, sizeof(P));
	FOR(i, MAX) {
		FOR(j, MAX)
			graph[i][j] = INF;
		FOR(j, 1 << (MAX - 1))
			D[i][j] = INF;
	}

	cin >> n >> m;
	rowCnt = 1 << (n - 1);

	FOR(i, m) {
		int u, v, w;
		cin >> u >> v >> w;
		graph[u][v] = w;
	}

	Solve();

	PrintPath(1, rowCnt-1);
	printf("%d\n", D[1][rowCnt - 1]);

	for (int i = 1; i <= n; i++) { 
		for (int j = 0; j < rowCnt; j++) {
			printf("%d", P[i][j]);
			if (j != rowCnt - 1)
				printf(" ");
		}
		printf("\n");
	}

	return 0;
}