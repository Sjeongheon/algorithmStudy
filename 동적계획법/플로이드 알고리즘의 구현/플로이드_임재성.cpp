#include<iostream>
#define MAX 130

using namespace std;


int W[MAX][MAX];
int D[MAX][MAX];
int P[MAX][MAX];

void floyd2(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			P[i][j] = 0;
			D[i][j] = W[i][j];
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
		}
	}
}

void path(int q, int r ) {
	if (P[q][r] != 0) {
		path(q, P[q][r]);
		cout << P[q][r] << " ";
		path(P[q][r], r);
	}
}

void printMatrix(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (D[i][j] > 9999) {
				cout << "INF" << " ";
				continue;
			}
			cout << D[i][j] << " ";
		}
		cout << "\n";
	}
}

void printMatrix2(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << P[i][j] << " ";
		}
		cout << " \n";
	}
}
int main() {
	int n, m, t,tempv,tempu,tempw;
	cin >> n >> m;

	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			W[i][j] = 10000;
			P[i][j] = 0;
		}
	}

	for (int i = 1;i <= n;i++) {
		W[i][i] = 0;
	}

	for (int i = 1;i <= m;i++) {
		cin >> tempu >> tempv >> tempw;
		W[tempu][tempv] = tempw;
	}
	floyd2(n);
	printMatrix(n);
	printMatrix2(n);
	cin >> t;

	for (int i = 0; i < t;i++) {
		cin >> tempu >> tempv;
		if (D[tempu][tempv] > 9999) {
			cout << tempu << " ";
			cout << tempv << " ";
			cout << "INF" << "\n";
		}
		else {
			cout << tempu << " ";
			path(tempu, tempv);
			cout << tempv << " ";
			cout << D[tempu][tempv] << "\n";
		}
	}
}
