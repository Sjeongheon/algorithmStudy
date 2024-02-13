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

struct Item {
	int id;
	int w;
	int p;
	int ef;
};

vector<Item> items;
bool compare(const Item& a, const Item& b) {
	return a.ef > b.ef;
}
int n;
int T;
int Weight;
vector<int> include;
vector<int> bestset;

int maxProfit;
int maxWeight;
int maxBound;

//Bound�� ���
int calcBound(int i, int w, int p) {
	i++;
	int bound = p;

	while (i < n) {
		if (items.at(i).w + w <= Weight) {
			bound += items.at(i).p;
			w += items.at(i).w;
		}
		else {
			bound += (Weight - w) * items.at(i).ef;
			break;
		}
		i++;
	}

	return bound;
}

//�� ������ �ʿ䰡 �ִ��� �˻�
bool Promising(int bound) {
	return bound > maxProfit;
}

//������� ����� item�� i���� �϶� �������� ����� �ִ������� max�� ����
//w : ������� ���� �뷮, p : ��������� profit
void Solve(int i, int w, int p) {
	int bound = calcBound(i, w, p);
	if (p > maxProfit) {
		maxProfit = p;
		maxWeight = w;
		maxBound = bound;
		FOR(j, i)
			bestset[j] = include[j];
	}

	if (!Promising(bound)) return;
	if (i >= n - 1) return;

	if (w + items.at(i+1).w <= Weight) {
		include.at(i + 1) = 1;
		Solve(i + 1, w + items.at(i + 1).w, p + items.at(i + 1).p);
	}
	include.at(i + 1) = 0;
	Solve(i + 1, w, p);
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;
	items.resize(n);
	include.resize(n,0);
	bestset.resize(n,0);
	FOR(i, n) {
		int wei;
		cin >> wei;
		items[i].id = i;
		items[i].w = wei;
	}

	FOR(i, n) {
		int pro;
		cin >> pro;
		items[i].p = pro;
		items[i].ef = items[i].p / items[i].w;
	}

	sort(items.begin(), items.end(), compare);

	cin >> T;
	FOR(t, T) {
		maxProfit = 0;
		maxWeight = 0;
		maxBound = 0;
		include.clear(); include.resize(n, 0);
		bestset.clear(); bestset.resize(n, 0);

		cin >> Weight;
		Solve(-1, 0, 0);
		printf("%d %d %d\n", maxProfit, maxWeight, maxBound);
	}

	return 0;
}