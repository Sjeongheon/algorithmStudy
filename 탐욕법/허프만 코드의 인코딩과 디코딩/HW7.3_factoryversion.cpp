/*
* [2018113300] [송정헌] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않
고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 27

using namespace std;

typedef struct node* node_pointer;
typedef struct node {
	char symbol;
	int frequency;
	node_pointer left;
	node_pointer right;
} nodetype;
node* root;

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
typedef struct position {
	char sym;
	vector<int> pos;
}position;
vector<position> huffmantree;

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
void preorder(node* current, vector<int> p) {
	if (current != NULL) {
		if (current->left == NULL && current->right == NULL) {
			position cur = { current->symbol, p };
			huffmantree.push_back(cur);
		}
		p.push_back(0);
		preorder(current->left, p);
		p.pop_back();
		p.push_back(1);
		preorder(current->right, p);
	}
}

vector<int> encoding() {
	int n;
	cin >> n;
	char target;
	vector<int> encode;
	for (int i = 0; i < n; i++) {
		cin >> target;
		for (int j = 0; j < huffmantree.size(); j++)
		{
			if (huffmantree[j].sym == target)
				for (int k = 0; k < huffmantree[j].pos.size(); k++)
					encode.push_back(huffmantree[j].pos[k]);
		}
	}

	return encode;
}
vector<char> decoding() {
	int n;
	cin >> n;
	vector<char> decode;
	int dir;
	node* traverse = root;
	for (int i = 0; i < n; i++)
	{
		cin >> dir;
		if (dir == 1)
			traverse = traverse->right;
		else
			traverse = traverse->left;

		if (traverse->left == NULL && traverse->right == NULL)
		{
			decode.push_back(traverse->symbol);
			traverse = root;
		}
	}
	return decode;
}

int main() {
	root = huffman();
	vector<int> p;
	preorder(root, p);
	vector<vector<char>> decode;
	vector<vector<int>> encode;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		encode.push_back(encoding());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < encode[i].size(); j++)
		{
			cout << encode[i][j];
			if (j != encode[i].size() - 1)
				cout << " ";
		}
		cout << endl;
	}


	cin >> n;
	for (int i = 0; i < n; i++)
		decode.push_back(decoding());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < decode[i].size(); j++)
		{
			cout << decode[i][j];
			if (j != decode[i].size() - 1)
				cout << " ";
		}
		cout << endl;
	}
}
