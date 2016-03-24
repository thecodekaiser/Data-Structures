// Author: thecodekaiser
// This code finds the maximum number in a given range and also finds the no of its occurances in that range
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long LL;
#define INF 1000007

template <typename T> T gcd(T a, T b)
{
	if(a % b == 0) return b;
	else	       return gcd(b, a%b);
}

template <typename T> T lcm(T a, T b)
{	return a * b / gcd(a,b);	}


template <typename T> pair<T,int> combine(pair<T,int> A, pair<T, int> B)
{
	if(A.first > B.first)
		return A;
	if(B.first > A.first)
		return B;
	return make_pair(A.first, A.second + B.second);
}


template <typename T> class SEG
{

private:
	T * copyArr;
	pair<T,int> * tree;
	int len;

	// Function : To build the tree
	void build(int Node, int l, int r)
	{
		if(l == r)
		{
			tree[Node] = make_pair(copyArr[l],1);
		}
		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
			build(left, l, mid);
			build(right, mid+1, r);
	
			tree[Node] = combine(tree[left],tree[right]);
		}
	}

	// Query operation
	pair<int,int> query(int Node, int l, int r, int i, int j)
	{
		if(i > r || j < l)	return make_pair(-INF,0);

		if(i <= l and j >= r) 	return tree[Node];

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
			pair<int,int> p1 = query(left, l, mid, i, j);
			pair<int,int> p2 = query(right, mid+1, r, i, j);
		
			return combine(p1,p2);
		}
	} 

	// Update operation	
	void update(int Node, int l, int r, int i, T value)
	{
	//	cout << "NODE: " << Node << " L: " << l << ",R: " << r << " i: " << i << " value: " << value << endl;

		if(i < l || i > r) return;
		else if(l == r)   tree[Node] = make_pair(value, 1);
		else
		{
			int left = 2 * Node , right = 2 * Node + 1, mid = (l+r)/ 2;
				
			if(i <= mid)
				update(left, l, mid, i, value);
			else
				update(right, mid+1, r, i, value);

			tree[Node] = combine(tree[left], tree[right]);
		}	
	}

public:
	// Constructor
	SEG(T * arr, int N)
	{
		len = N;
		copyArr = (T *) malloc (len * sizeof(T));
		tree	= (pair<int,int> *) malloc (4 * len * sizeof(pair<int,int>));

		for(int i = 0; i < len; i++)
			copyArr[i] = arr[i];
	
		build(1, 0, len - 1);
	}

	// Query
	void query(int i, int j)
	{
		pair<int,int> result = query(1, 0, len-1, i, j);
		cout << result.first << " --> " << result.second << endl;
	}
	
	// Updation
	void update(int i, T value)
	{
		copyArr[i] = value;
		update(1, 0, len-1, i, value);
	}

};
	

int main()
{
	int N, Q, c, l, r, val;
	cin >> N;
	int ptr[N];

	for(int i = 0; i < N; i++)
		cin >> ptr[i];

	SEG<int> st = SEG<int>(ptr,N);	

	cin >> Q;
	for(int i = 0; i < Q; i++)
	{
		cin >> c;
		if (c == 0)
		{
			cin >> l >> val;
			st.update(l-1, val);
		}
		else
		{
			cin >> l >> r;
			st.query(l-1, r-1);
		}
	}
	return 0;
}	
