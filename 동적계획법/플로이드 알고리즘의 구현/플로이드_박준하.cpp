/*
* 2018114686 박준하 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 130
#define INF -1

int N, M;
int D[MAX][MAX];	//경로의 길이를 저장
int P[MAX][MAX];	//경로를 추적하기 위해 사용
int T;

//그래프를 표현하는 행렬 출력
void Printgraph(int graph[][MAX]) {
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (graph[i][j] == INF)
				printf("INF ");
			else
				printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
}

//s에서 d까지의 경로를 s와 d를 제외하고 개행없이 출력
void Print_throughPath(int s, int d) {
	if (P[s][d] == 0) return;

	Print_throughPath(s, P[s][d]);
	printf("%d ", P[s][d]);
	Print_throughPath(P[s][d], d);
}

//s와 d를 포함해 출력
void PrintPath(int s, int d) {
	printf("%d ", s);
	Print_throughPath(s, d);
	printf("%d ", d);
}

void Floyd() {
	int d, i, j;
	for (d = 1; d < N + 1; d++) {
		for (i = 1; i < N + 1; i++) {
			for (j = 1; j < N + 1; j++) {
				if (D[i][d] == INF || D[d][j] == INF)
					continue;

				if (D[i][j] == INF ||
					D[i][j] > D[i][d] + D[d][j])
				{
					D[i][j] = D[i][d] + D[d][j];
					P[i][j] = d;
				}
			}
		}
	}
}

int main() {
	//입력 및 초기화
	scanf("%d %d", &N, &M);
	memset(D, INF, sizeof(D));
	memset(P, 0, sizeof(P));

	for (int i = 0; i < N + 1; i++) {
		D[i][i] = 0;
	}

	for (int m = 0; m < M; m++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		D[u][v] = w;
	}

	//플로이드 알고리즘 실행 후 출력
	Floyd();

	Printgraph(D);
	Printgraph(P);

	//테스트 케이스별 시작지점, 도착지점 입력후 경로 탐색
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int s, d;
		scanf("%d %d", &s, &d);
		PrintPath(s, d);

		if (D[s][d] == INF)
			printf("INF");
		else
			printf("%d\n", D[s][d]);
	}

	return 0;
}