// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

// Struct: For the trie
struct Node {
	Node * arr[26];
	Node()
	{
		for(int i = 0; i < 26; i++) 		
			arr[i] = NULL;
	}
	~Node()
	{
		for(int i = 0; i < 26; i++)
			if(arr[i] != NULL)			
				delete arr[i];	
	}
};

// Class Trie
class Trie
{
private:
	// Instance Variables
	Node * root;

	Node * getNode()
	{
		Node * res = new Node();

		for(int i = 0; i < 26; i++)  res -> arr[i] = NULL;
		return res;
	}

	void del(Node * curr)
	{
		for(int i = 0; i < 26; i++)
			if(curr -> arr[i] != NULL) del(curr -> arr[i]);

		delete curr;
	}

	

public:
	// Constructor
	Trie()	
	{
		root = new Node();
	}

	~Trie()
	{
		delete root;
	}

	// Function: Search
	int search(string& word)
	{
		int len = word.length(), lev, idx;

		Node * curr = root;
		for(lev = 0; lev < len; lev++)
		{
			idx = word[lev] - 'a';
			if(curr -> arr[idx] == NULL)
				return lev;
			
		 	curr = curr -> arr[idx];
		}
	
		return (lev-1);	
	}

	// Function: Insert
	void insert(string& word)
	{
		int len = word.length(), lev, idx;

		Node * curr = root;
		for(lev = 0; lev < len; lev++)
		{
			idx = word[lev] - 'a';
			if(curr -> arr[idx] == NULL)
				curr -> arr[idx] = new Node();

			curr = curr -> arr[idx];
		}

		return;
	}
};

void solve(int CS)
{
	int N;
	cin >> N;

	string str;
	Trie T;

	int total = 0;

	for(int i = 0; i < N; i++)
	{
		cin >> str;

		total += (T.search(str) + 1);
			
		T.insert(str);
	}

	printf("Case #%d: %d\n",CS, total);

	return;
}

int main()
{
	int t, CS = 1;
	cin >> t;

	while(t--) 	solve(CS++);
	
	return 0;
}
