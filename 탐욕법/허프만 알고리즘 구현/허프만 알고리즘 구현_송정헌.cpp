/*
* [2018113300] [송정헌] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않
고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 28

using namespace std;

typedef struct node* node_pointer;
typedef struct node {
	char symbol;
	int frequency;
	node_pointer left;
	node_pointer right;
} nodetype;
node* root;
node* rightend;
node_pointer create_node(char symbol, int frequency) {
	node_pointer node = (node_pointer)malloc(sizeof(nodetype));
	node->symbol = symbol;
	node->frequency = frequency;
	node->left = node->right = NULL;
	return node;
}
struct compare {
	bool operator()(node_pointer p, node_pointer q) {
		if (p->frequency > q->frequency)
			return true;
		return false;
	}
};

node* huffman() {
	int n;
	int frequency[MAX];
	char symbol[MAX];
	priority_queue<node_pointer, vector<node_pointer>, compare> PQ;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> symbol[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> frequency[i];
	}
	for (int i = 0; i < n; i++)
		PQ.push(create_node(symbol[i], frequency[i]));
	node* p, q, r;
	while (PQ.size() != 1) {
		node* p = PQ.top(); PQ.pop();
		node* q = PQ.top(); PQ.pop();
		node* r = create_node(' ', p->frequency + q->frequency);
		r->left = p;
		r->right = q;
		r->frequency = p->frequency + q->frequency;
		PQ.push(r);
	}
	return PQ.top();
}
void preorder(node* current) {
	if (current != NULL) {
		if (rightend == current)
			cout << current->symbol;
		else if (current->left == NULL && current->right == NULL)
			cout << current->symbol << " ";
		else
			cout << current->frequency << " ";
		preorder(current->left);
		preorder(current->right);
	}
}
void inorder(node* current) {
	if (current != NULL) {
		inorder(current->left);
		if (rightend == current)
			cout << current->symbol;
		else if (current->left == NULL && current->right == NULL)
			cout << current->symbol << " ";
		else
			cout << current->frequency << " ";
		inorder(current->right);
	}
}

int main() {
	root = huffman();
	rightend = root;
	while (rightend->right != NULL)
		rightend = rightend->right;
	preorder(root);
	cout << endl;
	inorder(root);

}
