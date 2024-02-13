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
vector<int> S;
vector<vector<int>> L;

//[low, high] 범위에서 가장 큰 수의 idx를 리턴
int Solve(int low, int high) {
	if (low == high) return low;

	int mid = (low + high) / 2;
	
	int left = Solve(low, mid);
	int right = Solve(mid + 1, high);

	int winner;
	if (S[left] > S[right]) {
		winner = left;
		L[winner].push_back(right);
	}
	else {
		winner = right;
		L[winner].push_back(left);
	}

	return winner;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	S.resize(n);
	L.resize(n);
	FOR(i, n) {
		cin >> S[i];
	}
	int maxidx = Solve(0, n - 1);

	vector<int>& loser = L[maxidx];
	int maxval = -1;
	FOR(i, loser.size()) {
		printf("%d", S[loser[i]]);
		if (i != loser.size() - 1)
			printf(" ");
		maxval = max(maxval, S[loser[i]]);
	}
	printf("\n%d", maxval);

	return 0;
}