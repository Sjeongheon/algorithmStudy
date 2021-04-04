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
const int MAX = 55000;
const int MOD = 100000000;

int T;
int n, k;
int B[MAX];
int row = 0;

//row-1 의 B를 이용하여 row를 계산.
void Calc_nextrow() {
	row += 1;

	int tmp = B[0];
	for (int i = 1; i < row + 1; i++) {
		int here = B[i];
		B[i] = (tmp + here) % MOD;
		tmp = here;
	}

#ifdef DEBUG
	printf("row : %d\n", row);
	FOR(i, row + 1) {
		printf("%d ", B[i]);
	}
	cout << endl;
#endif // DEBUG
}

//현재 n, k에 해당하는 이항계수 값을 리턴
int Solve() {
	//기저사례
	if (k == 0 || n == k) return 1;

	while (row < n) Calc_nextrow();
	return B[k];
}

int main() {
	//입력 및 초기화
	cin >> T;
	memset(B, 0, sizeof(B));
	B[0] = 1;

	FOR(t, T) {
		cin >> n >> k;
		cout << Solve() << endl;
	}

	return 0;
}