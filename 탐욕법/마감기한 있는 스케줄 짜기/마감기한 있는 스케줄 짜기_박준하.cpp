/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include <algorithm>
using namespace std;

//#define DEBUG
#define FOR(i, n) for(int i = 0; i < n; i++)

struct JOB {
	int number;
	int deadline;
	int profit;
};

int n;
vector<JOB> jobs;

bool isFeasible(vector<JOB>& K) {
	for (int i = 0; i < K.size(); i++) {
		if (K[i].deadline < i + 1) return false;
	}
	return true;
}

//jobarr에 있는 job이 deadline기준으로 오름차순이 되도록 newjob을 삽입한다.
void InsertNewJob(vector<JOB>& jobarr, JOB newjob) {
	auto it = jobarr.begin();
	for (it; it != jobarr.end(); it++) {
		if ((*it).deadline > newjob.deadline)
			break;
	}
	
	jobarr.insert(it, newjob);
}

int Solve() {
	//profit기준 내림차순 정렬
	vector<JOB> J;
	vector<JOB> K;

	auto it = jobs.begin();
	J.push_back(*it);
	it++;
	//하나씩 더해가면서 feasible 한지 확인
	for (it; it != jobs.end(); it++) {
		K.clear();
		K.resize(J.size());
		copy(J.begin(), J.end(), K.begin());

		//K에 새로운 원소 넣기
		InsertNewJob(K, *it);

		//만약 feasible 하다면 J에도 똑같이 넣어준다
		if (isFeasible(K)) {
			InsertNewJob(J, *it);
		}
	}

	//최종적으로 남은 요소들이 정답이 됨
	int result = 0;
	for (JOB job : J) {
		result += job.profit;
	}
	return result;
}

bool compareByProfit(JOB a, JOB b) {
	return a.profit > b.profit;
}

int main() {
	cin >> n;
	jobs.resize(n);
	int tmp;

	FOR(i, n) {
		jobs[i].number = i;
		cin >> tmp;
		jobs[i].deadline = tmp;
	}
	FOR(i, n) {
		cin >> tmp;
		jobs[i].profit = tmp;
	}

	sort(jobs.begin(), jobs.end(), compareByProfit);

	int result = Solve();
	printf("%d", result);
	
	return 0;
}