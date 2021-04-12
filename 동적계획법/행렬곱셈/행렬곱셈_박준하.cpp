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
int n;
int d[MAX];
int D[MAX][MAX];
int P[MAX][MAX];

//삼각형 모양으로 행렬의 부분을 출력
void PrintMat(int mat[MAX][MAX]) {
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			printf("%d", mat[i][j]);
			if (j != n) printf(" ");
		}
		printf("\n");
	}
}

//As ~ Ae 까지의 곱셈의 순서를 출력
void PrintPath(int s, int e) {
	if (s == e) {
		printf("A%d", s);
		return;
	}

	int mid = P[s][e];
	printf("(");
	PrintPath(s, mid);
	PrintPath(mid+1, e);
	printf(")");
}

//D[r][c]를 계산해내는 함수
void Calculate(int r, int c) {
	if (c - r <= 1) {
		D[r][c] = d[r - 1] * d[r] * d[c];
		P[r][c] = r;
		return;
	}

	int min = 1234567890;
	int idx = 0;
	for (int k = r; k < c; k++) {
		int tmp = D[r][k] + D[k + 1][c] + (d[r - 1] * d[k] * d[c]);
		if (tmp < min) {
			min = tmp;
			idx = k;
		}
	}

	D[r][c] = min;
	P[r][c] = idx;
}

void Solve() {
	for (int di = 1; di < n; di++) {
		for (int i = 1; i <= n - di; i++) {
			Calculate(i, i + di);
		}
	}
}

//메모이제이션
//As ~ Ae 까지의 곱에서 최적값을 계산
//int Solve(int s, int e) {
//	if (D[s][e] != -1) return D[s][e];
//
//	if (e == s) {
//		D[s][e] = 0;
//		return 0;
//	}
//	if (e - s == 1) {
//		D[s][e] = d[s - 1] * d[s] * d[e];
//		P[s][e] = s;
//		return D[s][e];
//	}
//
//	int min = 1234567890;
//	int idx = 0;
//	for (int i = s; i < e; i++) {
//		int tmp = Solve(s, i) + Solve(i + 1, e) + (d[s - 1] * d[i] * d[e]);
//		if (tmp < min) {
//			min = tmp;
//			idx = i;
//		}
//	}
//
//	D[s][e] = min;
//	P[s][e] = idx;
//	return D[s][e];
//}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		scanf("%d", &d[i]);
	}

	memset(D, 0, sizeof(D));
	memset(P, 0, sizeof(P));

	Solve();
	PrintMat(P);
	PrintMat(D);
	PrintPath(1, n);

	return 0;
}