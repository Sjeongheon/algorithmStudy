/*
* 2018114686 ������ ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
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
int T;
vector<int> solutions;
vector<int> path;

//�Ķ���͸� ���� �ʰ� path.size()�� ��ġ�� �˾Ƴ�
bool Promising() {
	int len = path.size();
	int k = 0;

	while (k < len - 1) {
		if (path.at(k) == path.at(len - 1)) return false;
		else if (len - 1 - k == abs(path.at(len - 1) - path.at(k))) return false;
		k++;
	}

	return true;
}

void Solve() {
	if (!Promising()) return;

	if (path.size() == n) {
		string paths;
		for (int it : path) paths.push_back(it + 1 + '0');
		solutions.push_back(stoi(paths));
	}
	else {
		for (int i = 0; i < n; i++) {
			path.push_back(i);
			Solve();
			path.pop_back();
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;

	Solve();

	cin >> T;
	FOR(i, T) {
		int tmp;
		cin >> tmp;
		bool flag = false;
		for (int s : solutions) {
			if (s == tmp) {
				flag = true;
				break;
			}
		}
		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}