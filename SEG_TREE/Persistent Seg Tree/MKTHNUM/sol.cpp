// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 100010
#define GETC getchar_unlocked()

int revM[MXN], arr[MXN];
map<int,int> mp;
int N, M, x, y, k;

// Function: To read
template <typename T> T read()
{
	T n = 0;
	int ch = GETC, sign = 1;
	while(ch < '0' or ch > '9') { if(ch == '-') sign = -1; ch = GETC; }	
	while(ch >= '0' and ch <= '9')
	{
		n = n * 10 + ch - '0';
		ch = GETC;
	}
	n *= sign;
	return n;
}


// This code uses Persistent Segment Tree to solve the problem
struct Node
{
	int count;
	Node * left, * right;	// Children
	
	Node(int count, Node * left, Node * right):
		count(count), left(left), right(right) {}

	Node * insert(int l, int r, int val);
};

Node * base = new Node(0, NULL, NULL);		// This is the base node which we use for our leaf nodes
Node * root[MXN];							// These will be the N seg trees

// Function: To insert a new node
Node * Node::insert(int l, int r, int val)
{
	// If it's in the range..then we need a new node
	if(l <= val and val <= r)
	{
		if(l == r)
			return new Node(this->count+1, base, base);
			
		int mid = (l + r) >> 1;
		return new Node(this->count+1, this->left->insert(l, mid, val), this->right->insert(mid+1, r, val));
	}
	
	// Else use previous node
	return this;
}

// Function: Query the index of the kth element in the range [L, R].. we can do it using f(R) - f(L-1).. supposing function f gives us the ans
int query(Node * L, Node * R, int i, int j, int k)
{
	if(i == j)
		return i;
		
	int mid = (i + j) >> 1;
	int lCount = (R -> left -> count) - (L -> left -> count);
	if(lCount >= k)
		return query(L->left, R->left, i, mid, k);
	else
		return query(L->right, R->right, mid+1, j, k-lCount);
	
}

void solve()
{
	N = read<int>(), M = read<int>();
	
	for(int i = 0; i < N; i++)
	{
		arr[i] = read<int>();
		
		mp[arr[i]];		// We are creating an entry in the map.. it will be useful in coordinate compression
	}
	
	int lmt = 0;
	
	// Doing the coordinate compression.. that is I am compressing all values in the range [0,N)
	for(map<int,int> :: iterator it = mp.begin(); it != mp.end(); it++)
	{
		mp[it->first] = lmt;
		revM[lmt] = it->first;	// This is the value at index lmt
		lmt++;
	}
	
	
	base -> left = base -> right = base;
	
	for(int i = 0; i < N; i++)
	{
		root[i] = (i == 0 ? base : root[i-1]) -> insert(0, lmt-1, mp[arr[i]]);
	}
	
	for(int i = 0; i < M; i++)
	{
		x = read<int>(), y = read<int>(), k = read<int>();
		
		x--, y--;
		
		int ans = query((x == 0 ? base : root[x-1]), root[y], 0, lmt-1, k);
		printf("%d\n", revM[ans]);
	}
	
	return;
}

int main()
{
	solve();
	return 0;
}
