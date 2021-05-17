
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#define MAX 256
using namespace std;

int w[MAX], p[MAX], P[MAX][MAX], W;
void knapsack2(int n, int W, int w[], int p[], int P[][MAX]);
int main() {
	int n, T, W;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= n; i++)
		cin >> p[i];

	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> W;
		knapsack2(n, W, w, p, P);
		cout << P[n][W] << " " << P[n - 1][W] << " " << P[n - 1][W - w[n]]<<"\n";
	}
}
void knapsack2(int n, int W, int w[], int p[], int P[][MAX]) {
	for (int i = 1; i <= n; i++)
		P[i][0] = 0;
	for (int j = 1; j <= W; j++)
		P[0][j] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= W; j++)
			P[i][j] = (w[i] > j) ? P[i - 1][j]:
			max(P[i - 1][j], p[i] + P[i - 1][j - w[i]]);
}