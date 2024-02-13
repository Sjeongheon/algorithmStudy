/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
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

int n;
vector<int> originalS;
vector<int> S;
int cnt = 0;

//[low, high] 범위의 배열에서 첫번째 요소를 pivot으로 하여 분할
//반환하는 것은 분할이 끝난 시점에서의 pivot point index
int Partition(int low, int high) {
	cnt++;
	int pivot = S[low];
	int j = low;
	for (int i = low + 1; i <= high; i++) {
		if (pivot > S[i]) {
			j++;
			swap(S[j], S[i]);
		}
	}

	swap(S[j], S[low]);
	return j;
}

//탐색범위를[low, high]로 제한해놓고 S에서 k번째로 작은 요소를 찾아 리턴
int Solve(int low, int high, int k) {
	if (low == high) return S[low];

	int pivotpoint = Partition(low, high);
	if (k == pivotpoint) return S[pivotpoint];
	else if (k < pivotpoint) return Solve(low, pivotpoint - 1, k);
	else return Solve(pivotpoint + 1, high, k);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	originalS.resize(n);

	FOR(i, n) {
		cin >> originalS[i];
	}

	int T;
	int k;
	cin >> T;
	FOR(i, T) {
		cin >> k;
		S = originalS;
		cnt = 0;
		//S의 idx가 0부터 시작하므로 k-1을 넣어준다.
		int result = Solve(0, n - 1, k-1);
		printf("%d %d\n", result, cnt);
	}

	return 0;
}