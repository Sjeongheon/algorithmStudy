#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
#pragma warning(disable : 4996)
#define MAX 30
bool promising(int i);
void m_coloring(int i);
int n, m;// 정점의 수 n, 간선의 수 m
int W[MAX][MAX];
int vcolor[MAX];
bool ok = false;
int main()
{
	cin >> n >> m;
	int edge1, edge2;//간선을 입력 받을 때, 두 간선 사이를 연결하는 정점
	for (int i = 1; i <= m; i++)
	{
		cin >> edge1 >> edge2;
		W[edge1][edge2] = true;
		W[edge2][edge1] = true;
	}
	int tmp = m;
	for (int i = 1; i <= tmp; i++)
	{
		m = i;
		m_coloring(0);
		if (ok == true)
		{
			cout << m;
			break;
		}
	}


	return 0;
}
void m_coloring(int i) {

	int color;
	if (promising(i)) {
		if (i == n)
		{
			ok = true;
		}

		else
			for (color = 1; color <= m; color++) {
				vcolor[i + 1] = color;
				m_coloring(i + 1);
			}
	}
}

bool promising(int i) {
	int j = 1;
	bool flag = true;
	while (j < i && flag) {
		if (W[i][j] && vcolor[i] == vcolor[j])
			flag = false;
		j++;
	}
	return flag;
}
