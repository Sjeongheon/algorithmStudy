
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 256
using namespace std;

typedef struct item* item_pointer;
typedef struct item {
	int id;
	int weight;
	int profit;
	float unit_profit;
}itemtype;
struct compare {
	bool operator()(item_pointer a, item_pointer b) {
		return a->unit_profit < b->unit_profit;
	}
};
void initialize_PQ(priority_queue<item_pointer, vector<item_pointer>, compare> &PQ1, int n1, int w1[], int p1[]);
void knapsack1(int n, int W, int w[], int p[]);
int w[MAX], p[MAX];
int main() {
	int n, T, W;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	cin >> T;
	for (int i = 1; i <= T; i++) {
		cin >> W;
		knapsack1(n, W, w, p);
	}
}
void initialize_PQ(priority_queue<item_pointer, vector<item_pointer>, compare> &PQ1, int n1, int w1[], int p1[]) {
	for (int i = 1; i <= n1; i++) {
		item_pointer item = (item_pointer)malloc(sizeof(itemtype));
		item->id = i;
		item->weight = w1[i];
		item->profit = p1[i];
		item->unit_profit = (float)p1[i] / (float)w1[i];
		PQ1.push(item);
	}
}
void knapsack1(int n, int W, int w[], int p[]) {
	priority_queue<item_pointer, vector<item_pointer>, compare> PQ;
	initialize_PQ(PQ, n, w, p);
	int total_weight = 0;
	int total_profit = 0;
	while (!PQ.empty()) {
		item_pointer i = PQ.top();
		PQ.pop();
		total_weight += i->weight;
		if (total_weight > W) {
			int diff = i->weight - (total_weight - W);
			float profit = diff * (i->unit_profit);
			total_weight = total_weight - i->weight + diff;
			total_profit+=profit;
			//cout << "(*" << i->id << "," << diff << "," << profit << ")" << endl;
			break;
		}
		total_profit += i->profit;
		//cout << "(" << i->id << "," << i->weight << "," << i->profit << ")" << endl;
	}
	cout << total_weight << " " << total_profit << "\n";
}