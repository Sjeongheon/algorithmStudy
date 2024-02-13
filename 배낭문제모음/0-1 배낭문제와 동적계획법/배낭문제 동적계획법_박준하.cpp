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
//시험칠때 index 밀리는 것 주의할것//
/////////////////////////////////////

//가방 용량이 W 남았을때 [0, range]범위의
//item으로 만들 수 있는 최대이익 반환
int Solve(int range, int w) {
	//캐시확인
	auto it = cache.find(make_pair(range, w));
	if (it != cache.end())
		return (*it).second;

	//기저사례
	if (range == 0) {
		return weights[0] <= w ? profits[0] : 0;
	}

	//재귀부
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