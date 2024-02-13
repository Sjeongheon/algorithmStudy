/*
* 2018114686 ������ ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
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

//[low, high] ������ �迭���� ù��° ��Ҹ� pivot���� �Ͽ� ����
//��ȯ�ϴ� ���� ������ ���� ���������� pivot point index
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

//Ž��������[low, high]�� �����س��� S���� k��°�� ���� ��Ҹ� ã�� ����
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
		//S�� idx�� 0���� �����ϹǷ� k-1�� �־��ش�.
		int result = Solve(0, n - 1, k-1);
		printf("%d %d\n", result, cnt);
	}

	return 0;
}