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
//[low, high]구간의 중앙값을 리턴
//구간의 길이는 반드시 5여야 함
int Median(vector<int>&S, int low, int high) {
	vector<int> sec(S.begin() + low, S.begin() + high + 1);

	//비교 1 : sec[0] <= sec[1] 로 만든다
	if (sec[0] > sec[1]) swap(sec[0], sec[1]);

	//비교 2 : sec[2] <= sec[3] 으로 만든다
	if (sec[2] > sec[3]) swap(sec[2], sec[3]);

	//비교 3 : [0,3]중 가장 작은 것을 sec[4]로 대체한다
	if (sec[0] > sec[2]) {
		swap(sec[1], sec[3]);
		swap(sec[0], sec[2]);
	}
	sec[0] = sec[4];

	//비교 4 : sec[0] <= sec[1] 로 만든다
	if (sec[0] > sec[1]) swap(sec[0], sec[1]);

	//비교 5 : 4개중에 가장 작은 걸 없에고
	//sec[0] <= sec[1], sec[3] 상태로 만든다
	if (sec[0] < sec[2]) {
		sec[0] = sec[2];
		swap(sec[1], sec[3]);
	}

	//비교 6 : 3개중 가장 작은 것을 리턴(sec[0], sec[3]중 작은걸 리턴)
	return min(sec[0], sec[3]);
}
*/

//[low, high]구간의 중앙값을 리턴
int Median(vector<int>&S, int low, int high) {
	vector<int> sec(S.begin() + low, S.begin() + high + 1);
	sort(sec.begin(), sec.end());
	return sec[(sec.size() - 1) / 2];
}

//[low, high] 범위의 배열에서 median을 pivot으로 하여 분할
//반환하는 것은 분할이 끝난 시점에서의 pivot point index
int Partition(vector<int>& S, int low, int high) {
	cnt++;
	int size = high - low + 1;
	vector<int> medians;
	//S를 5개 단위의 구간들로 나눈다
	int section_num = (int)ceil((double)(size) / 5);

	//각 구간의 중앙값을 계산
	for (int i = 0; i < section_num; i++) {
		int start = low + i * 5;
		int end = min(start + 4, high);
		medians.push_back(Median(S, start, end));
	}
	//중앙값들의 중앙값을 찾는다
	int median_of_median = Select(medians, (section_num-1) / 2);

	//최종 중앙값을 기준으로 parition
	int j = low - 1; //mom과 같거나 작은 요소가 들어간 마지막 자리
	int mark = -1;	 //pivot이 들어가있는 자리
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

//탐색범위를[low, high]로 제한해놓고 S에서 k번째로 작은 요소를 찾아 리턴
int Solve(vector<int>& S, int low, int high, int k) {
	if (low == high) return S[low];

	int pivotpoint = Partition(S, low, high);
	if (k == pivotpoint) return S[pivotpoint];
	else if (k < pivotpoint) return Solve(S, low, pivotpoint - 1, k);
	else return Solve(S, pivotpoint + 1, high, k);
}

//오름차순으로 정렬했을때 S[k]를 리턴
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
		//S의 idx가 0부터 시작하므로 k-1을 넣어준다.
		int result = Solve(S, 0, n - 1, k-1);
		printf("%d %d\n", result, cnt);
	}

	return 0;
}