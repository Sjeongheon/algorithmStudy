#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
#pragma warning(disable : 4996)
#define MAX 30
void sum_of_subsets(int i, int weight, int total);
bool promising(int i, int weight, int total);
int W;// 부분집합의 합
int w[MAX];//전체 집합
int include[MAX];//부분 집합
int cnt = 0;

int main()
{
	int n, num, total = 0;
	cin >> n;
	cin >> W;
	for (int i = 1; i <= n; i++)
	{
		cin >> num;
		w[i] = num;
		total += num;
	}

	sum_of_subsets(0, 0, total);
	cout << cnt;
}

void sum_of_subsets(int i, int weight, int total) {
	if (promising(i, weight, total)) {
		if (weight == W) {
			/*			for (int k = 1; k <= i; k++)
						{
						cout << include[k];
						}
				cout << "다음다음다음다음";
				*/
			cnt++;
		}

		else {
			include[i + 1] = true;
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = false;
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}
	}
}

bool promising(int i, int weight, int total) {
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

