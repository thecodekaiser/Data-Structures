// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

struct Node
{
	Node * arr[26];
};

Node * getNode()
{
	Node * res = (Node *) malloc (sizeof(Node));

	for(int i = 0; i < 26; i++)
		res -> arr[i] = NULL;
}


void insert_word(Node * root, string word)
{
	Node * curr = root;
	int len = word.length();
	int lev, idx;

	for(lev = 0; lev < len; lev++)
	{
		idx = word[idx] - '0';

		if(curr -> arr[idx] == NULL) curr -> arr[idx] = getNode();
		curr = curr -> arr[idx];
	}
		
	return;
}

int search_word(Node * root, string word)
{
	Node * curr = root;
	int len = word.length();
	int lev, idx;

	
	for(lev = 0; lev < len; lev++)
	{
		idx = word[idx] - '0';
		cout << "idx: " << idx << endl;
		if(curr -> arr[idx] == NULL) return lev;
		curr = curr -> arr[idx];
	}
	
	return (lev-1);
}

void solve(int CS)
{
	int N;
	cin >> N;

	int total = 0, cnt;
	string str;
	Node * root = getNode();

	for(int i = 0; i < N; i++)
	{
		cin >> str;
		cnt = search_word(root, str);
		cout << cnt << " ";
		total += cnt;

		insert_word(root, str);
	}	
	cout << endl;
	printf("Case #%d: %d\n",CS, total);
	return;
}

int main()
{
	int t, CS = 1;
	cin >> t;

	while(t--)
		solve(CS++);
	
	return 0;
}
