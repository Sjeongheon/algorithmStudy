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
	//test case�� � �������� queens�Լ��ȿ��� �ڵ����� �����Ǵ� ������, 
	//���� ���ؾ��ϴ� ������ �Ǵ��ϱ�
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
	if (promising(i)) {// n�� �̸� ������ ������ex)4
		if (i == n)
		{
			for (int a = 1; a <= n; a++)
			{
				solution[s] = solution[s] + col[a] * pow(10, n - a);
			}
			//(test)cout <<s << "��° �ַ��� �迭��"<< solution[s]<<endl;
			s++;
		}
		else
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queens(i + 1);
			}
	}
}

bool promising(int i) {//���� col�� �ִ��� ������,�밢���� �ִ��� ������ �˻��ϴ� �Լ�
	int k = 1;
	bool flag = true;
	while (k < i && flag) {
		if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k))
			flag = false;
		k++;
	}
	return flag;
}