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
    char symbol;   // ���ڰ�
    int frequency; // ���Ͽ� �ִ� ������ �󵵼�

    struct nodetype* left;
    struct nodetype* right;
}node;

typedef struct pq   // �켱���� ��⿭
{
    node* Node;         // ��⿭�� �ִ� node
    struct pq* next;   // ���� node
}pq;

#define ROOT    -1 // ��ȣȭ �Լ� ��½� �ʱⰪ

void decode(char* str, node* root);
pq* insert(node* r);        // �켱���� ��⿭�� ��带 �����Ͽ� ����
node* huffman(int n);       // ������ �ڵ� Ʈ���� ����� �Լ�
node* Remove();             // �켱 ���� ��⿭���� ��带 ����
void print_PQ();            // �켱 ���� ��⿭ ���
void print_tree(node* r, int n, char* code);    // ��� ������ ��ȣȭ ���
void freetree(node* r);     // �޸� ����
int n, frequency[MAX];
char symbol[MAX];
pq* PQ = NULL;      // �켱���� ��⿭

map<char, string> m1;

int main()
{
    scanf("%d", &n);
    char c1;
    int fre;
    node* result = (node*)malloc(sizeof(node));   // ����� �������� ���
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

    result = huffman(n);    // ������ �˰���
    print_tree(result, ROOT, code);
    int test = 0;
    int num = 0;
    char ch;
    scanf("%d", &test);//��ü �׽�Ʈ���̽�
    for (int i = 0; i < test; i++)
    {
        scanf("%d", &num);//�� �տ� ����
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

    scanf("%d", &test);//��ü �׽�Ʈ���̽�
    char* encode;
    for (int i = 0; i < test; i++)
    {
        scanf("%d", &num);//�� �տ� ����
        encode = (char*)calloc(sizeof(char), num + 1);

        for (int j = 0; j < num; j++)
        {
            scanf(" %c", &encode[j]);
        }
        decode(encode, result);
    }

    freetree(result);   // �޸� ����


    return 0;
}


void print_tree(node* r, int k, char* code) // ��� ������ �˰���  Ʈ�� ���
{
    if (r) {
        k++;    // Ʈ���� ���̸� ǥ��

        code[k] = '0';    // Ʈ���� ����
        print_tree(r->left, k, code);

        code[k] = '1';    // Ʈ���� ����
        print_tree(r->right, k, code);

        code[k] = '\0';   // ��� ����
        if (r->left == NULL || r->right == NULL) {// �ڽ��� �ִ� ���� ������� ����
            m1.insert(make_pair(r->symbol, code));
        }
    }

}

void decode(char* str, node* root)
{
    string answer = "";
    int i = 0;
    node* j = root;
    while (str[i] != '\0') //������ ���� �ƴ� ���
    {
        if (str[i] == '0') //���ڰ� 0�� ���
            j = j->left; //���� �ڽ����� �̵�
        else if (str[i] == '1') //���ڰ� 1�� ���
            j = j->right; //������ �ڽ����� �̵�
        if (j->left == NULL && j->right == NULL) //�� ����� ���
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


void freetree(node* r)  // �޸� ����
{
    if (r) {
        freetree(r->left);
        freetree(r->right);
        free(r);
    }
}

pq* insert(node* r) // �켱���� ��⿭�� ��� ����
{
    pq* tmp = NULL;
    pq* new1 = NULL;

    // �켱���� ��⿭ �߰��� ���ο� ���� �Ҵ�
    new1 = (pq*)malloc(sizeof(pq));
    new1->Node = r;      // ��⿭�� �߰��� ���ο� ������ r ��尪 ����
    new1->next = NULL;

    if (PQ == NULL) {    // ��⿭�� �������� ���ο� ������ ����Ʈ�� head�� ��
        PQ = new1;
        return PQ;
    }
    else if (PQ->Node->frequency > new1->Node->frequency) {
        new1->next = PQ;             // ��Ʈ ��忡 ���� �� �� ����
        PQ = new1;
    }
    else {                            // ��⿭�� ����Ʈ�� ��� �ִٸ�..
        tmp = PQ;                       // tmp�� head
        while (tmp->next != NULL) {        // ���� ��尡 ����������..
            if (tmp->next->Node->frequency <= new1->Node->frequency)
                tmp = tmp->next;        // �켱���� ��⿭ ������ ���� ��
            else {                       // new�� �󵵼��� tmp ���� ũ��,
                new1->next = tmp->next;  // tmp->next�� �󵵼����� ������..  
                tmp->next = new1;        // �� ��� ���̿� �� ��带 ����
                break;
            }

        }
        if (tmp->next == NULL)     // ���� ��⿭�� ��� ������ ����
            tmp->next = new1;

        return tmp;
    }
    return 0;
}

node* huffman(int n)    // ������ �˰���
{
    node* p;
    node* q;
    node* r;

    int i;

    for (i = 1; i <= n - 1; i++) {
        p = Remove();   // �켱 ���� ��⿭���� �ϳ��� ��带 ���ͼ� p�� ����
        q = Remove();   // �켱 ���� ��⿭���� �ϳ��� ��带 ���ͼ� q�� ����

        r = (node*)malloc(sizeof(node)); // ���ο� �κ� Ʈ���� ���� ���� �Ҵ�
        r->left = p;
        r->right = q;
        r->frequency = p->frequency + q->frequency;
        r->symbol = '*';  // �κ� Ʈ���� �Ѹ����� ��Ÿ��
        insert(r);          // ������� �κ� Ʈ���� �켱 ���� ��⿭�� ����

        //printf("-- Create sub tree (%d/%d)\n  ", i, n-1);
        //printf("%c:%d = %c:%d + %c:%d\n",
            //r->symbol, r->frequency, p->symbol, p->frequency, q->symbol, q->frequency);
        //print_PQ();
    }

    r = Remove();   // �켱 ���� ��⿭�� �ִ� Ʈ���� �Ѹ��� ���ͼ� r�� ����
    return r;
}

node* Remove()  // �켱 ���� ��⿭���� �ϳ��� ��带 ���� ���ϰ����� �ѱ��
{
    node* pq_firstnode = NULL;

    pq_firstnode = PQ->Node;
    PQ = PQ->next;

    return pq_firstnode;
}
