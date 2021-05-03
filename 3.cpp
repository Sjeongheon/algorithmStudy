#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;
#pragma warning(disable : 4996)
#define MAX 30
typedef struct nodetype
{
    char symbol;   // 문자값
    int frequency; // 파일에 있는 문자의 빈도수

    struct nodetype* left;
    struct nodetype* right;
}node;

typedef struct pq   // 우선순위 대기열
{
    node* Node;         // 대기열에 있는 node
    struct pq* next;   // 다음 node
}pq;

#define ROOT    -1 // 부호화 함수 출력시 초기값

void decode(char* str, node* root);
pq* insert(node* r);        // 우선순위 대기열에 노드를 정렬하여 삽입
node* huffman(int n);       // 허프만 코드 트리를 만드는 함수
node* Remove();             // 우선 순위 대기열에서 노드를 삭제
void print_PQ();            // 우선 순위 대기열 출력
void print_tree(node* r, int n, char* code);    // 결과 허프만 부호화 출력
void freetree(node* r);     // 메모리 해제
int n, frequency[MAX];
char symbol[MAX];
pq* PQ = NULL;      // 우선순위 대기열

map<char, string> m1;

int main()
{
    scanf("%d", &n);
    char c1;
    int fre;
    node* result = (node*)malloc(sizeof(node));   // 결과를 돌려받을 노드
    char* code = (char*)malloc(sizeof(char));
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", &c1);
        symbol[i] = c1;
    }
    for (int j = 1; j <= n; j++)
    {
        scanf("%d", &fre);
        frequency[j] = fre;
    }

    for (int k = 1; k <= n; k++)
    {
        node* r = (node*)malloc(sizeof(node));
        r->symbol = symbol[k];
        r->frequency = frequency[k];
        r->left = NULL;
        r->right = NULL;
        insert(r);
    }

    result = huffman(n);    // 허프만 알고리즘
    print_tree(result, ROOT, code);
    int test = 0;
    int num = 0;
    char ch;
    scanf("%d", &test);//전체 테스트케이스
    for (int i = 0; i < test; i++)
    {
        scanf("%d", &num);//맨 앞에 숫자
        for (int j = 1; j <= num; j++)
        {
            scanf("%s", &ch);
            if (j == num)
            {
                bool first = true;
                for (char c : m1[ch]) {
                    if (!first) printf(" ");
                    first = false;
                    printf("%c", c);
                }
                cout << endl;
            }
            else
            {
                for (char c : m1[ch]) {
                    printf("%c ", c);
                }
            }
        }
    }

    scanf("%d", &test);//전체 테스트케이스
    char* encode;
    for (int i = 0; i < test; i++)
    {
        scanf("%d", &num);//맨 앞에 숫자
        encode = (char*)calloc(sizeof(char), num + 1);

        for (int j = 0; j < num; j++)
        {
            scanf(" %c", &encode[j]);
        }
        decode(encode, result);
    }

    freetree(result);   // 메모리 해제


    return 0;
}


void print_tree(node* r, int k, char* code) // 결과 허프만 알고리즘  트리 출력
{
    if (r) {
        k++;    // 트리의 깊이를 표시

        code[k] = '0';    // 트리의 좌측
        print_tree(r->left, k, code);

        code[k] = '1';    // 트리의 우측
        print_tree(r->right, k, code);

        code[k] = '\0';   // 찌꺼기 제거
        if (r->left == NULL || r->right == NULL) {// 자식이 있는 노드는 출력하지 않음
            m1.insert(make_pair(r->symbol, code));
        }
    }

}

void decode(char* str, node* root)
{
    string answer = "";
    int i = 0;
    node* j = root;
    while (str[i] != '\0') //문자의 끝이 아닌 경우
    {
        if (str[i] == '0') //문자가 0인 경우
            j = j->left; //왼쪽 자식으로 이동
        else if (str[i] == '1') //문자가 1인 경우
            j = j->right; //오른쪽 자식으로 이동
        if (j->left == NULL && j->right == NULL) //단 노드인 경우
        {
            answer += j->symbol;
            j = root;
        }
        i++;
    }
    for (int q = 0; q < answer.size(); q++)
    {
        printf("%c", answer[q]);
        printf("%c", q + 1 == answer.size() ? '\n' : ' ');
    }
}


void freetree(node* r)  // 메모리 해제
{
    if (r) {
        freetree(r->left);
        freetree(r->right);
        free(r);
    }
}

pq* insert(node* r) // 우선순위 대기열에 노드 삽입
{
    pq* tmp = NULL;
    pq* new1 = NULL;

    // 우선순위 대기열 추가할 새로운 공간 할당
    new1 = (pq*)malloc(sizeof(pq));
    new1->Node = r;      // 대기열에 추가할 새로운 공간에 r 노드값 삽입
    new1->next = NULL;

    if (PQ == NULL) {    // 대기열이 비여있으면 새로운 공간이 리스트의 head가 됌
        PQ = new1;
        return PQ;
    }
    else if (PQ->Node->frequency > new1->Node->frequency) {
        new1->next = PQ;             // 루트 노드에 대한 비교 및 정렬
        PQ = new1;
    }
    else {                            // 대기열에 리스트가 들어 있다면..
        tmp = PQ;                       // tmp는 head
        while (tmp->next != NULL) {        // 다음 노드가 없을때까지..
            if (tmp->next->Node->frequency <= new1->Node->frequency)
                tmp = tmp->next;        // 우선순위 대기열 정렬을 위한 비교
            else {                       // new의 빈도수가 tmp 보다 크고,
                new1->next = tmp->next;  // tmp->next의 빈도수보다 작으면..  
                tmp->next = new1;        // 두 노드 사이에 새 노드를 삽입
                break;
            }

        }
        if (tmp->next == NULL)     // 다음 대기열이 비어 있으면 삽입
            tmp->next = new1;

        return tmp;
    }
    return 0;
}

node* huffman(int n)    // 허프만 알고리즘
{
    node* p;
    node* q;
    node* r;

    int i;

    for (i = 1; i <= n - 1; i++) {
        p = Remove();   // 우선 순위 대기열에서 하나의 노드를 빼와서 p에 삽입
        q = Remove();   // 우선 순위 대기열에서 하나의 노드를 빼와서 q에 삽입

        r = (node*)malloc(sizeof(node)); // 새로운 부분 트리를 위한 공간 할당
        r->left = p;
        r->right = q;
        r->frequency = p->frequency + q->frequency;
        r->symbol = '*';  // 부분 트리의 뿌리임을 나타냄
        insert(r);          // 만들어진 부분 트리를 우선 순위 대기열에 삽입

        //printf("-- Create sub tree (%d/%d)\n  ", i, n-1);
        //printf("%c:%d = %c:%d + %c:%d\n",
            //r->symbol, r->frequency, p->symbol, p->frequency, q->symbol, q->frequency);
        //print_PQ();
    }

    r = Remove();   // 우선 순위 대기열에 있는 트리의 뿌리를 빼와서 r에 대입
    return r;
}

node* Remove()  // 우선 순위 대기열에서 하나의 노드를 빼서 리턴값으로 넘긴다
{
    node* pq_firstnode = NULL;

    pq_firstnode = PQ->Node;
    PQ = PQ->next;

    return pq_firstnode;
}
