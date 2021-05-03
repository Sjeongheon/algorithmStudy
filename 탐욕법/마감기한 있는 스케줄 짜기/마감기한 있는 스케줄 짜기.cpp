/*
* [2018113300] [송정헌] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않
고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 17
typedef vector<int> sq_of_int;

typedef struct inf {
	int index;
	int dl;
	int pr;
}input;
int compare(const void* a, const void* b)
{
	inf* num1 = (inf*)a;
	inf* num2 = (inf*)b;
	return num2->pr - num1->pr;
}

bool lemma(sq_of_int K, int deadline[]) {
	vector<int>::iterator it = K.begin();
	for (int i = 1; it != K.end(); it++, i++)
		if (i > deadline[*it])
			return false;
	return true;
}
void schedule(int n, int deadline[], sq_of_int& J) {
	int i;
	sq_of_int K;

	J = { 1 };
	for (i = 2; i <= n; i++) {
		K.resize(J.size());
		copy(J.begin(), J.end(), K.begin());
		vector<int>::iterator it = K.begin();
		for (; it != K.end(); it++)
		{
			if (deadline[*it] > deadline[i])
				break;
		}
		K.insert(it, i);

		if (lemma(K, deadline)) {
			J.resize(K.size());
			vector<int>::iterator it = J.begin();
			for (; it != K.end(); it++)
				
			copy(K.begin(), K.end(), J.begin());
		}
	}
}
int main() {
	int N;
	inf Input[MAX];
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> Input[i].dl;
		Input[i].index = i;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> Input[i].pr;
	}
	qsort(Input, N, sizeof(inf), compare);

	sq_of_int sq;
	int DL[MAX];
	for (int i = 0; i < N; i++)
	{
		DL[i + 1] = Input[i].dl;
	}
	schedule(N, DL, sq);
	int total = 0;
	for (int i = 0; i < sq.size(); i++)
	{
		total += Input[sq[i] - 1].pr;
	}
	cout << total;

}