// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int words, prefixes;
	Node * arr[26];

	Node()
	{
		words = prefixes = 0;
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

class Trie
{
private:
	// Instance variables
	Node * root;		

public:
	// Constructor
	Trie()
	{
		root = new Node();
	}

	// Destructor
	~Trie()
	{
		delete root;
	}

	// Function: Insert
	void insert(string word)
	{
		int len = word.length(), lev, idx;

		Node * curr = root;
		
		for(lev = 0; lev < len; lev++)
		{
			idx = word[lev] - 'a';

			curr -> prefixes += 1;			// The current string is a prefix of some other string
			
			if(curr -> arr[idx] == NULL)	curr -> arr[idx] = new Node();

			curr = curr -> arr[idx];
		}

		curr -> prefixes += 1;		// A complete word is a also a prefix of itself
		curr -> words += 1;		// Here a new word ends
	}

	// Function: Counts the no of words which have given string as a prefix
	int countPrefixes(string word)
	{
		int len = word.length(), lev, idx;
		
		Node * curr = root;
		
		for(lev = 0; lev < len; lev++)
		{
			idx = word[lev] - 'a';
			
			if(curr -> arr[idx] == NULL)	
				return 0;
			
			curr = curr -> arr[idx];
		}

		return curr -> prefixes;
	}

	// Function: Counts the no of words which are the same as the given string
	int countWords(string word)
	{
		int len = word.length(), lev, idx;
		
		Node * curr = root;
		
		for(lev = 0; lev < len; lev++)
		{
			idx = word[lev] - 'a';
			
			if(curr -> arr[idx] == NULL)	
				return 0;
			
			curr = curr -> arr[idx];
		}

		return curr -> words;
	}
};

void solve()
{
	int N, M;
	
	cin >> N >> M;

	string str;
	Trie T;


	for(int i = 0; i < N; i++)
	{
		cin >> str;
		T.insert(str);
	}

	for(int i = 0; i < M; i++)
	{
		cin >> str;
		cout << T.countPrefixes(str) << endl;
	}

	return;
}

int main()
{
	int t;
	cin >> t;

	while(t--)	solve();
	return 0;
}
