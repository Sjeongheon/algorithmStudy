/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)

int n;
int W;
vector<int> w;
vector<bool> include;
int cnt = 0;

bool Promising(int curSum, int total, int i) {
	if (i == n - 1 && curSum != W) return false;
	else if (curSum != W && curSum + w.at(i + 1) > W) return false;
	else if (curSum + total < W) return false;
	else return true;
}

void Solve(int i, int total, int curSum) {
	if (!Promising(curSum, total, i)) return;

	if (i >= n - 1) cnt++;
	else {
		include[i + 1] = true;
		Solve(i + 1, total - w[i + 1], curSum + w[i + 1]);
		include[i + 1] = false;
		Solve(i + 1, total - w[i + 1], curSum);
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n >> W;
	FOR(i, n) {
		int tmp;
		cin >> tmp;
		w.push_back(tmp);
	}

	sort(w.begin(), w.end());
	include.resize(n, false);

	int total = 0;
	for (int it : w)
		total += it;

	Solve(-1, total, 0);
	cout << cnt;

	return 0;
}