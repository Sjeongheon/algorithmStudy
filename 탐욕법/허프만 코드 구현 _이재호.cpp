#include <stdio.h>
#include <stdlib.h>

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
void preorder(node* root);
void inorder(node* root);
pq* insert(node* r);        // �켱���� ��⿭�� ��带 �����Ͽ� ����
node* huffman(int n);       // ������ �ڵ� Ʈ���� ����� �Լ�
node* Remove();             // �켱 ���� ��⿭���� ��带 ����
void print_PQ();            // �켱 ���� ��⿭ ���
void print_tree(node* r, int n, char* code);    // ��� ������ ��ȣȭ ���
void freetree(node* r);     // �޸� ����
int n, frequency[MAX];
char symbol[MAX];
pq* PQ = NULL;      // �켱���� ��⿭

int print_results[MAX * 4];
int print_key = 0;

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


    //printf("### Huffman Algorithm ###\n\n");
    //print_PQ();     // �Է��� ���� �켱���� ��⿭

    result = huffman(n);    // ������ �˰���

    print_key = 0;
    preorder(result);
    for (int i = 0; i < print_key; ++i) {
        if (print_results[i] == -1)
            printf("%d", print_results[++i]);
        else
            printf("%c", print_results[++i]);

        printf("%c", i + 1 == print_key ? '\n' : ' ');
    }

    print_key = 0;
    inorder(result);
    for (int i = 0; i < print_key; ++i) {
        if (print_results[i] == -1)
            printf("%d", print_results[++i]);
        else
            printf("%c", print_results[++i]);

        printf("%c", i + 1 == print_key ? '\n' : ' ');
    }

    //printf("\n-- Result Huffman code tree\n");
    //print_tree(result, ROOT, code);
    //printf("\n");

    //freetree(result);   // �޸� ����

    return 0;
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

void preorder(node* root) {
    if (root->symbol == '*') {
        print_results[print_key++] = -1;
        print_results[print_key++] = root->frequency;
    }
    else {
        print_results[print_key++] = -2;
        print_results[print_key++] = root->symbol;
    }
    if (root->left != NULL)
        preorder(root->left);
    if (root->right != NULL)
        preorder(root->right);
}

void inorder(node* root) {
    if (root->left != NULL)
        inorder(root->left);
    if (root->symbol == '*') {
        print_results[print_key++] = -1;
        print_results[print_key++] = root->frequency;
    }
    else {
        print_results[print_key++] = -2;
        print_results[print_key++] = root->symbol;
    }if (root->right != NULL)
        inorder(root->right);
}

void print_PQ()     // �켱���� ��⿭ ���
{
    pq* tmp = PQ;
    printf("-- Priority Queue\n  | ");
    while (tmp != NULL) {
        printf("%c:%d | ", tmp->Node->symbol, tmp->Node->frequency);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void print_tree(node* r, int n, char* code) // ��� ������ �˰���  Ʈ�� ���
{
    if (r) {
        n++;    // Ʈ���� ���̸� ǥ��

        code[n] = '0';    // Ʈ���� ����
        print_tree(r->left, n, code);

        code[n] = '1';    // Ʈ���� ����
        print_tree(r->right, n, code);

        code[n] = '\0';   // ��� ����
        if (r->left == NULL || r->right == NULL)   // �ڽ��� �ִ� ���� ������� ����
            printf(" - %c:%d\t= %s\n", r->symbol, r->frequency, code);
    }
}