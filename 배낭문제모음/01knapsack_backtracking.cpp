
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#define MAX 256
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
using namespace std;

bool include[MAX], bestset[MAX];
int maxprofit, maxweight;
int w[MAX], p[MAX], W, n;
float unit_weight[MAX];
float bound_temp;
float bound;
void sorting(int n, int w[], int p[], float unit_weight[]);
void knapsack(int i, int profit, int weight);
void array_copy(bool include[], bool bestset[]);
bool promising(int i, int profit, int weight);

int main() {
	int T;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= n; i++)
		unit_weight[i] = (float)p[i]/w[i];
	sorting(n, w, p, unit_weight);

	cin >> T;
	for (int i = 1; i <= T; i++) {
		maxprofit = 0;
		maxweight = 0;
		bound = 0;
		cin >> W;
		knapsack4(0, 0, 0);
		cout << maxprofit << " " << maxweight << " "<<bound<<"\n";
	}
}
void sorting(int n, int w[], int p[], float unit_weight[]){
	int i, j, temp=0;
	for (i = n; i > 1; i--)
		for (j = 1; j < i; j++)
			if (unit_weight[j] < unit_weight[j + 1]) {
				SWAP(unit_weight[j], unit_weight[j + 1], temp);
				SWAP(w[j], w[j + 1], temp);
				SWAP(p[j], p[j + 1], temp);
			}
}
void knapsack(int i, int profit, int weight) {
	if (weight <= W && profit > maxprofit) {
		maxweight = weight;
		maxprofit = profit;
		bound = bound_temp;
		array_copy(include, bestset);
	}
	if (promising(i, profit, weight)) {
		include[i + 1] = true;
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = false;
		knapsack(i + 1, profit, weight);
	}
}
void array_copy(bool include[], bool bestset[]) {
	for (int i = 1; i <= sizeof(include) / sizeof(int); i++)
		bestset[i] = include[i];
}
bool promising(int i, int profit, int weight) {
	int j, k, totweight;
	if (weight >= W)
		return false;
	else {
		j = i + 1;
		bound_temp = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight += w[j];
			bound_temp += p[j];
			j++;
		}
		k = j;
		if (k <= n) {
			bound_temp += (W - totweight) * ((float)p[k] / w[k]);
		}
		return bound_temp > maxprofit;
	}
}