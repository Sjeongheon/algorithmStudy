#include<stdio.h>
#include<iostream>

using namespace std;

int B[50001];
int cur;

void Bi(int n, int k) {
	int j;
	for (;cur <= n;cur++) {
		B[cur] = 1;
		for (j = cur-1 ;j >= cur/2;j--) {
			B[j] = (B[j] + B[j - 1])% 100000000;
		}
		B[j] = B[j+2];
	}


	/*cout << "ÇöÀç ¼ö¿­:" ;
	for (int i = 0;i < cur;i++) {
		cout << B[i] << "  ";
	}
	cout << "\n" << "cur: "<< cur << endl;*/


	if (k < n / 2) {
		printf("%d\n", B[cur-1-k]);
	}
	else {
		printf("%d\n", B[k]);
	}
}

int main() {
	int t,tempn,tempk;
	cur = 0;
	scanf("%d", &t);
	for (int i = 0;i < t;i++) {
		scanf("%d %d", &tempn, &tempk);
		Bi(tempn, tempk);
	}
}

/*****************************박준하********************************
뒤에서 부터 계산한다는게 이말이었군요. 군더더기 없이 깔끔하게 잘 짜신것 같아요
*******************************************************************/
