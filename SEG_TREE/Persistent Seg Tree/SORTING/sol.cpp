// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 500500
#define GETC getchar_unlocked()

int ptr[MXN];
int pos[MXN];
int N, M, x, y, k, val;

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

// Function: Gives the Kth value in the range [i,j]
int getKth(int i, int j, int k)
{	
	if(i > j)
		swap(i,j);
				
	int ans = query((i == 0 ? base : root[i-1]), root[j], 0, N-1, k);
	
	return ans;
}

// Function: This is the main function
ll rec(int L, int R)
{
	stack< pair<int,int> > st;
	ll ans = 0;
	
	st.push(pair<int,int>(L,R));
	pair<int,int> temp;
	
	while(!st.empty())
	{
		temp = st.top();
		st.pop();
		
		int i = temp.first, j = temp.second;
		//cout << "i: " << i << " j: " << j << endl;
		
		if(j <= i)
			continue;
		else
		{
			int pivot = getKth(i, j, (j-i+2)/2);
			pivot = pos[pivot];
			
			//cout << "PIVOT: " << pivot << endl;
			
			ans += (j-i+1);
			
			st.push(pair<int,int>(i, pivot-1));
			st.push(pair<int,int>(pivot+1, j));
		}
	}
	
	return ans;
}

void solve()
{
	N = read<int>();
	
	for(int i = 0; i < N; i++)
	{
		val = read<int>();
		val--;
		
		ptr[val] = i;
		pos[i] = val;
	}
			
	base -> left = base -> right = base;
	
	for(int i = 0; i < N; i++)
	{
		root[i] = (i == 0 ? base : root[i-1]) -> insert(0, N-1, ptr[i]);
	}
	
	//int ans = getKth(0, N-1, (N-1 - 0 + 2)/2);
	
	//cout << ans << " " << pos[ans] << endl;
	
	ll res = rec(0,N-1);
	
	cout << res << endl;
	
	return;
}

int main()
{
	solve();
	return 0;
}
