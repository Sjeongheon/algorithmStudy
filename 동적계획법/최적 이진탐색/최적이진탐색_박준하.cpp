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
int K[MAX];
int p[MAX];
int A[MAX][MAX];
int P[MAX][MAX];

void PrintMat(int mat[MAX][MAX]) {
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			printf("%d", mat[i][j]);
			if (j != n)
				printf(" ");
		}
		printf("\n");
	}
}

//r~c 까지의 노드를 전위순회로 출력한다
void PrintPreorder(int r, int c, vector<int>& arr) {
	if (r > c) return;
	if (r == c) {
		arr.push_back(K[r]);
		return;
	}

	int root = P[r][c];
	arr.push_back(K[root]);
	PrintPreorder(r, root - 1, arr);
	PrintPreorder(root + 1, c, arr);
}

//r~c 까지의 노드를 중위순회로 출력한다
void PrintInorder(int r, int c, vector<int>& arr) {
	if (r > c) return;
	if (r == c) {
		arr.push_back(K[r]);
		return;
	}

	int root = P[r][c];
	PrintInorder(r, root-1, arr);
	arr.push_back(K[root]);
	PrintInorder(root + 1, c, arr);
}

void Calculate(int r, int c) {
	if (r >= c) return;

	int psum = 0;
	for (int i = r; i <= c; i++)
		psum += p[i];

	int min = 1234567890;
	int idx = 0;
	for (int i = r; i <= c; i++) {
		int tmp = A[r][i - 1] + A[i + 1][c] + psum;
		if (tmp < min) {
			min = tmp;
			idx = i;
		}
	}

	A[r][c] = min;
	P[r][c] = idx;
}

void Solve() {
	for (int di = 1; di < n; di++) {
		for (int i = 1; i <= n - di; i++) {
			int j = i + di;
			Calculate(i, j);
		}
	}
}

//메모이제이션
//[s, e] 범위의 노드를 가지고 만들 수 있는 최적 이진 트리의 최적값 계산
//int Solve(int s, int e) {
//	if (A[s][e] != -1) return A[s][e];
//	else if (s == e) {
//		A[s][e] = p[s];
//		P[s][e] = s;
//		return A[s][e];
//	}
//	else if (s > e) {
//		A[s][e] = 0;
//		return A[s][e];
//	}
//
//	int psum = 0;
//	for (int i = s; i <= e; i++) {
//		psum += p[i];
//	}
//
//	int min = 1234567890;
//	int idx = 0;
//	for (int i = s; i <= e; i++) {
//		int tmp = Solve(s, i - 1) + Solve(i + 1, e) + psum;
//		if (tmp < min) {
//			min = tmp;
//			idx = i;
//		}
//	}
//
//	A[s][e] = min;
//	P[s][e] = idx;
//	return A[s][e];
//}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &K[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &p[i]);

	memset(A, 0, sizeof(A));
	memset(P, 0, sizeof(P));
	for (int i = 1; i <= n; i++) {
		A[i][i] = p[i];
		P[i][i] = i;
	}

	Solve();

	PrintMat(A);
	PrintMat(P);
	
	vector<int> arr;
	PrintPreorder(1, n, arr);
	for (int i = 0; i < arr.size(); i++) {
		printf("%d", arr[i]);
		if (i != arr.size() - 1)
			printf(" ");
	}
	printf("\n");

	arr.clear();
	PrintInorder(1, n, arr);
	for (int i = 0; i < arr.size(); i++) {
		printf("%d", arr[i]);
		if (i != arr.size() - 1)
			printf(" ");
	}
	printf("\n");
	
	return 0;
}