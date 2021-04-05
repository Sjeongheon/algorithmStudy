//이 코드랑 앞의 두 코드 모두 스스로 짰습니다. 2020114665 임재성.
#include<iostream>
#include<vector>
#define MAX 129

using namespace std;

int A[MAX][MAX];
int D[MAX][MAX];
int P[MAX][MAX];

void bottomup(int n) {
	for (int i = 1;i <= n;i++) {
		D[n][i] = A[n][i];
	}
	for (int i = n;i > 1;i--) {
		for (int j = 1;j < i;j++) {
			if (D[i][j] > D[i][j + 1]) {//앞이 클때
				P[i - 1][j] = 0;
				D[i - 1][j] = A[i - 1][j] + D[i][j];
			}
			else {//뒤가 크거나 같을때
				P[i - 1][j] = 1;
				D[i - 1][j] = A[i - 1][j] + D[i][j+1];
			}
		}
	}
}

void path(int n) {
	int j=1;
	cout << A[1][1] << " ";
	for (int i = 1;i < n;i++) {
		if (P[i][j] == 1) {
			j++;
			cout << A[i+1][j] << " ";
		}
		else {
			cout << A[i+1][j] << " ";
		}
	}
}

void print1(int n) {
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= i;j++) {
			cout << D[i][j] <<" ";
		}
		cout << "\n";
	}
}
void print2(int n) {
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= i;j++) {
			cout << P[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	int n,temp;
	cin >> n;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= i;j++) {
			cin >> temp;
			A[i][j] = temp;
		}
	}
	bottomup(n);
	cout << D[1][1] << "\n";
	path(n);
	/*cout << "\n";
	cout << "\n";
	cout << "\n";
	print1(n);
	cout << "\n";
	cout << "\n";
	print2(n);*/
}