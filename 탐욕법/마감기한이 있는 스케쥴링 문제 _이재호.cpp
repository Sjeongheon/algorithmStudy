#include <stdio.h>
#include <stdlib.h>
#include <string>
#pragma warning(disable : 4996)

#define TRUE 1
#define FALSE 0
#define MAX 100


void sort();
int is_feasible(int len);
void insert(int i, int len);
void copyToFrom(int len, int A[], int B[]);
int schedule();

int J[MAX];
int K[MAX];
int deadline[MAX] = { 0, };
int profit[MAX] = { 0, };
int n;
int num[MAX] = { 0, };


int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &deadline[i]);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &profit[i]);
        num[profit[i]] = i;
    }

    sort();
    int len;
    len = schedule();
    int total = 0;

    for (int i = 1; i < len; i++)
        total += profit[J[i]];

    printf("%d", total);
}



void sort() {
    int temp = 0;
    int temp3 = 0;
    for (int i = 1; i < n; i++) {
        for (int k = i + 1; k <= n; k++) {
            if (profit[i] < profit[k]) {
                temp = profit[i];
                temp3 = deadline[i];
                profit[i] = profit[k];
                deadline[i] = deadline[k];
                profit[k] = temp;
                deadline[k] = temp3;
            }

        }
    }
}

int is_feasible(int len) {
    int i;
    for (i = 1; i <= len; i++)
        if (deadline[K[i]] < i)
            return FALSE;
    return TRUE;
}

void insert(int i, int len) {
    int j;
    for (j = len; j > 0; j--) {
        if (deadline[i] >= deadline[K[j - 1]])
            break;
        K[j] = K[j - 1];
    }
    K[j] = i;
}

void copyToFrom(int len, int A[], int B[]) {

    for (int i = 1; i <= len; i++) {
        A[i] = B[i];
    }

}


int schedule() {

    int i, j, length = 1;
    J[0] = K[0] = 0;
    J[length++] = 1;
    for (i = 2; i <= n; i++) {
        copyToFrom(length, K, J);  //K=J
        insert(i, length); //add i to K in non-decreasing order by deadlines
        if (is_feasible(length)) {
            copyToFrom(++length, J, K); //J=K
        }
    }
    return length;

}
