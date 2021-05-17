/*
* [2017114355] [박수빈] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/

#include <iostream>
#include <algorithm>
#define MAX 256
using namespace std;

typedef struct item {
    int weight, value;
} item;

item items[MAX];
int W[MAX];

int n;
bool cmp(item a, item b);
int knackValue(item items[], int n, int W);

int main() {
    int T;

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> items[i].weight;

    for (int i = 0; i < n; i++)
        cin >> items[i].value;

    // bound 기준으로 items를 내림차순 정렬
    sort(items, items + n, cmp);

    cin >> T;

    for (int i = 0; i < T; i++)
        cin >> W[i];

    for (int i = 0; i < T; i++)
        cout << knackValue(items, n, W[i]) << endl;
}

bool cmp(item a, item b) {
    int bound1 = a.value / a.weight;
    int bound2 = b.value / b.weight;

    return bound1 > bound2;
}

int knackValue(item items[], int n, int W) {
    int curWeight = 0;
    int finalValue = 0;

    for (int i = 0; i < n; i++)
        // 가방에 여유가 있으면
        if (curWeight + items[i].weight <= W) {
            curWeight += items[i].weight;
            finalValue += items[i].value;
        }

    // 여유가 없다면 분할해서 넣기
        else {
            int remain = W - curWeight;
            finalValue += items[i].value * remain / items[i].weight;
            curWeight += items[i].weight * remain / items[i].weight;

            //cout << items[i].value * remain / items[i].weight << "Test Test Test" << endl;
            break;
        }

    cout << curWeight << " ";

    return finalValue;
}