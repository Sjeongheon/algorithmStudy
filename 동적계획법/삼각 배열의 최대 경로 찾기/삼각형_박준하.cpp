/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 130

int N;
int T[MAX][MAX];	//원래 입력 값
int D[MAX][MAX];	//경로의 길이 저장
int P[MAX][MAX];	//경로 탐색용

void Solve() {
	//아랫층 부터 순서대로 순회
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < i+1; j++) {
			//바로아래, 오른쪽 아래 중 큰 것을 선택
			if (D[i+1][j] <= D[i+1][j + 1]) {
				P[i][j] = j + 1;
				D[i][j] += D[i + 1][j + 1];
			}
			else {
				P[i][j] = j;
				D[i][j] += D[i + 1][j];
			}
		}
	}
}

void PrintPath() {
	printf("%d ", T[0][0]);
	int nextIdx = P[0][0];
	for (int i = 1; i < N; i++) {
		printf("%d ", T[i][nextIdx]);
		nextIdx = P[i][nextIdx];
	}
}

int main() {
	//초기화 및 입력
	memset(T, 0, sizeof(T));
	memset(D, 0, sizeof(D));
	memset(P, 0, sizeof(P));

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < i+1; j++) {
			scanf("%d", &D[i][j]);
			T[i][j] = D[i][j];
		}
	}
	
	//알고리즘 실행 및 출력
	Solve();

	printf("%d\n", D[0][0]);
	PrintPath();

	return 0;
}