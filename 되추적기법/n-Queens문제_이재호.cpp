#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
#pragma warning(disable : 4996)
#define MAX 30
int n;
int col[MAX];
int solution[400];
void queens(int i);
bool promising(int i);
int s = 0;


int main()
{
	//test case가 몇개 나오는지 queens함수안에서 자동으로 생성되는 것인지, 
	//따로 구해야하는 것인지 판단하기
	int testcase;
	int testnum;
	cin >> n;
	queens(0);

	cin >> testcase;
	for (int i = 1; i <= testcase; i++)
	{

		cin >> testnum;
		bool TRUE = false;
		for (int k : solution)
		{
			if (testnum == k)
				TRUE = true;
		}
		if (TRUE)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}

void queens(int i) {
	int j;
	int k = 1;
	if (promising(i)) {// n은 미리 정해진 상태임ex)4
		if (i == n)
		{
			for (int a = 1; a <= n; a++)
			{
				solution[s] = solution[s] + col[a] * pow(10, n - a);
			}
			//(test)cout <<s << "번째 솔류션 배열값"<< solution[s]<<endl;
			s++;
		}
		else
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queens(i + 1);
			}
	}
}

bool promising(int i) {//같은 col에 있는지 없는지,대각선에 있는지 없는지 검사하는 함수
	int k = 1;
	bool flag = true;
	while (k < i && flag) {
		if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k))
			flag = false;
		k++;
	}
	return flag;
}