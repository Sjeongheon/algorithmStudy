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

struct Item {
	int weight;
	int profit;
	int efficiency;
};

bool compareItem(const Item& a, const Item& b) {
	return a.efficiency > b.efficiency;
}

struct Node {
	int weight;
	int profit;
	int bound;
	int level;

	Node(){}

	Node(int w, int p, int b, int l) {
		weight = w;
		profit = p;
		bound = b;
		level = l;
	}
};

class compareNode {
public:
	bool operator()(Node* a, Node* b) {
		return a->bound < b->bound;
	}
};

priority_queue<Node*, vector<Node*>, compareNode> pq;
vector<Item> items;
int n;
Node maxNode;
int cnt;

void calcBound(Node* node, int W){
	if (node->weight >= W) {
		node->bound = 0;
		return;
	}

	Node tmp = *node;
	while (tmp.level < n && tmp.weight < W) {
		if (tmp.weight + items[tmp.level + 1].weight <= W) {
			tmp.weight += items[tmp.level + 1].weight;
			tmp.profit += items[tmp.level + 1].profit;
			tmp.level += 1;
		}
		else {
			tmp.profit += items[tmp.level + 1].efficiency
				* (W - tmp.weight);
			tmp.weight = W;
			break;
		}
	}

	node->bound = tmp.profit;
}

void SolvePrint(int W) {
	Node* root = new Node(0, 0, 0, 0);
	calcBound(root, W);
	pq.push(root); cnt++;

	while (!pq.empty()) {
		Node* top = pq.top(); pq.pop();
		if (top->level >= n || top->bound <= maxNode.profit){
			free(top); continue;
		}

		int next = top->level + 1;

		Node* put = new Node(top->weight + items[next].weight, top->profit + items[next].profit, 0, next);
		calcBound(put, W);
		if (put->weight <= W && put->profit > maxNode.profit) {
			maxNode.profit = put->profit;
			maxNode.weight = put->weight;
			maxNode.bound = put->bound;
		}
		if (put->bound > maxNode.profit) {
			pq.push(put); cnt++;
		}

		Node* notPut = new Node(top->weight, top->profit, 0, next);
		calcBound(notPut, W);
		if (notPut->bound > maxNode.profit) {
			pq.push(notPut); cnt++;
		}

		free(top);
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	cin >> n;
	items.resize(n + 1);
	for (int i = 1; i <= n; i++){
		int w; cin >> w;
		items[i].weight = w;
	}
	for (int i = 1; i <= n; i++) {
		int p; cin >> p;
		items[i].profit = p;
		items[i].efficiency = items[i].profit / items[i].weight;
	}
	sort(items.begin()+1, items.end(), compareItem);

	int T; cin >> T;
	FOR(t, T) {
		int W; cin >> W;
		maxNode.profit = 0;
		cnt = 0;
		SolvePrint(W);
		printf("%d %d %d %d\n", maxNode.profit, maxNode.weight, maxNode.bound, cnt);
	}

	return 0;
}