/*
* [2017114355] [박수빈] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/

#include <iostream>
#define MAX 256
using namespace std;

typedef struct item {
    int weight, value;
} item;

item items[MAX];
int n;
int W[MAX];

void knapSack(int W, int num);

int main() {
    int T;

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> items[i].weight;

    for (int i = 0; i < n; i++)
        cin >> items[i].value;

    cin >> T;

    for (int i = 0; i < T; i++)
        cin >> W[i];

    for (int i = 0; i < T; i++)
        knapSack(W[i], n);
}

void knapSack(int W, int num) {
    int P[num + 1][W + 1];

    for (int i = 0; i <= num; i++)
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                P[i][j] = 0;

            else if (items[i - 1].weight <= j)
                P[i][j] = max(items[i - 1].value + P[i - 1][j - items[i - 1].weight], P[i - 1][j]);

            else
                P[i][j] = P[i - 1][j];
        }

    if (W > items[num - 1].weight)
        cout << P[num][W] << " " << P[num - 1][W] << " " << P[num - 1][W - items[num - 1].weight] << endl;

    else
        cout << P[num][W] << " " << P[num - 1][W] << " " << "0" << endl;

}