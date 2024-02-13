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
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)

int n, T;
vector<int> profits;
vector<int> weights;
map<pair<int, int>, int> cache;

/////////////////////////////////////
//����ĥ�� index �и��� �� �����Ұ�//
/////////////////////////////////////

//���� �뷮�� W �������� [0, range]������
//item���� ���� �� �ִ� �ִ����� ��ȯ
int Solve(int range, int w) {
	//ĳ��Ȯ��
	auto it = cache.find(make_pair(range, w));
	if (it != cache.end())
		return (*it).second;

	//�������
	if (range == 0) {
		return weights[0] <= w ? profits[0] : 0;
	}

	//��ͺ�
	int result = 0;

	int notPut = Solve(range - 1, w);
	int put = weights[range] > w ? 0 :
		profits[range] + Solve(range - 1, w - weights[range]);

	result = max(notPut, put);

	cache.insert(make_pair(make_pair(range, w), result));
	return result;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;
	profits.resize(n);
	weights.resize(n);

	FOR(i, n) {
		int w;
		cin >> w;
		weights[i] = w;
	}

	FOR(i, n) {
		int p;
		cin >> p;
		profits[i] = p;
	}

	cin >> T;
	FOR(t, T) {
		int W;
		cin >> W;
		cache.clear();
		int result = Solve(n - 1, W);

		auto it = cache.find(pair<int, int>(n - 2, W));
		int val1 = it != cache.end() ? it->second : 0;

		it = cache.find(pair<int, int>(n - 2, W - weights[n - 1]));
		int val2 = it != cache.end() ? it->second : 0;

		printf("%d %d %d\n", result, val1, val2);
	}

	return 0;
}