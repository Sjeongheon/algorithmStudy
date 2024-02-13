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
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF 123456789
#define MAX 10

int n;
vector<int> originalS;
vector<int> S;
int cnt = 0;

int Median(vector<int>&S, int low, int high);
int Partition(vector<int>&S, int low, int high);
int Solve(vector<int>&S, int low, int high, int k);
int Select(vector<int>&S, int k);

/*
//[low, high]������ �߾Ӱ��� ����
//������ ���̴� �ݵ�� 5���� ��
int Median(vector<int>&S, int low, int high) {
	vector<int> sec(S.begin() + low, S.begin() + high + 1);

	//�� 1 : sec[0] <= sec[1] �� �����
	if (sec[0] > sec[1]) swap(sec[0], sec[1]);

	//�� 2 : sec[2] <= sec[3] ���� �����
	if (sec[2] > sec[3]) swap(sec[2], sec[3]);

	//�� 3 : [0,3]�� ���� ���� ���� sec[4]�� ��ü�Ѵ�
	if (sec[0] > sec[2]) {
		swap(sec[1], sec[3]);
		swap(sec[0], sec[2]);
	}
	sec[0] = sec[4];

	//�� 4 : sec[0] <= sec[1] �� �����
	if (sec[0] > sec[1]) swap(sec[0], sec[1]);

	//�� 5 : 4���߿� ���� ���� �� ������
	//sec[0] <= sec[1], sec[3] ���·� �����
	if (sec[0] < sec[2]) {
		sec[0] = sec[2];
		swap(sec[1], sec[3]);
	}

	//�� 6 : 3���� ���� ���� ���� ����(sec[0], sec[3]�� ������ ����)
	return min(sec[0], sec[3]);
}
*/

//[low, high]������ �߾Ӱ��� ����
int Median(vector<int>&S, int low, int high) {
	vector<int> sec(S.begin() + low, S.begin() + high + 1);
	sort(sec.begin(), sec.end());
	return sec[(sec.size() - 1) / 2];
}

//[low, high] ������ �迭���� median�� pivot���� �Ͽ� ����
//��ȯ�ϴ� ���� ������ ���� ���������� pivot point index
int Partition(vector<int>& S, int low, int high) {
	cnt++;
	int size = high - low + 1;
	vector<int> medians;
	//S�� 5�� ������ ������� ������
	int section_num = (int)ceil((double)(size) / 5);

	//�� ������ �߾Ӱ��� ���
	for (int i = 0; i < section_num; i++) {
		int start = low + i * 5;
		int end = min(start + 4, high);
		medians.push_back(Median(S, start, end));
	}
	//�߾Ӱ����� �߾Ӱ��� ã�´�
	int median_of_median = Select(medians, (section_num-1) / 2);

	//���� �߾Ӱ��� �������� parition
	int j = low - 1; //mom�� ���ų� ���� ��Ұ� �� ������ �ڸ�
	int mark = -1;	 //pivot�� ���ִ� �ڸ�
	for (int i = low; i <= high; i++) {
		if (S[i] <= median_of_median) {
			j++;
			swap(S[j], S[i]);
			if (S[j] == median_of_median) mark = j;
		}
	}
	swap(S[j], S[mark]);
	return j;
}

//Ž��������[low, high]�� �����س��� S���� k��°�� ���� ��Ҹ� ã�� ����
int Solve(vector<int>& S, int low, int high, int k) {
	if (low == high) return S[low];

	int pivotpoint = Partition(S, low, high);
	if (k == pivotpoint) return S[pivotpoint];
	else if (k < pivotpoint) return Solve(S, low, pivotpoint - 1, k);
	else return Solve(S, pivotpoint + 1, high, k);
}

//������������ ���������� S[k]�� ����
int Select(vector<int>& S, int k) {
	int size = S.size();
	return Solve(S, 0, size-1, k);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> n;
	originalS.resize(n);

	FOR(i, n) {
		cin >> originalS[i];
	}

	int T;
	int k;
	cin >> T;
	FOR(i, T) {
		cin >> k;
		S = originalS;
		cnt = 0;
		//S�� idx�� 0���� �����ϹǷ� k-1�� �־��ش�.
		int result = Solve(S, 0, n - 1, k-1);
		printf("%d %d\n", result, cnt);
	}

	return 0;
}