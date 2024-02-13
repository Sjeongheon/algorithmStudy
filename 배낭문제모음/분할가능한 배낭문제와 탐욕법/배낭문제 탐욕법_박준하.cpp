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
#include <queue>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)

struct Item{
	int weight;
	int profit;
	int efficient;
	int id;
};

class compare {
public:
	bool operator()(const Item& a, const Item& b) {
		return a.efficient < b.efficient;
	}
};

int n, T;
priority_queue<Item, vector<Item>, compare> items;

void SovlePrint(int W) {
	int w = 0, p = 0;
	auto itemsCopy = items;

	while (!itemsCopy.empty()) {
		Item top = itemsCopy.top(); itemsCopy.pop();
		if (w + top.weight <= W) {
			w += top.weight;
			p += top.profit;
		}
		else {
			p += (W - w) * top.efficient;
			w = W;
			break;
		}
	}

	printf("%d %d\n", w, p);
}

//���� �ڵ� ��������
//total_weight -= i->weight; �������.
//int diff = W - total_weight;
int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;
	vector<int> weights(n);

	FOR(i, n) {
		int w;
		cin >> w;
		weights[i] = w;
	}

	FOR(i, n) {
		int p;
		cin >> p;
		Item tmp;
		tmp.weight = weights[i];
		tmp.profit = p;
		tmp.efficient = tmp.profit / tmp.weight;
		tmp.id = i;

		items.push(tmp);
	}

	cin >> T;
	FOR(t, T) {
		int W;
		cin >> W;
		SovlePrint(W);
	}
	
	return 0;
}