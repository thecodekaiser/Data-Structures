// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

/**
 * This code finds the smallest integer greater than or equal to a given integer in a given range.
 * It also allow modification requests.
 * It is implemented using the merge-sort tree.
 * Each segment is itself a multiset
 * Both query and update run in (lg N)^2 time.
 */

#define MXN 100010
#define INF 1000000007
#define GETC getchar_unlocked()

typedef long long ll;

multiset<ll> tree[4*MXN];		// This is the mergesort tree
ll arr[MXN];				// This is the actual array

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


void build(int Node, int l, int r)
{
	if(l == r)
	{
		tree[Node].insert(arr[l]);
		return;
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

	build(left, l, mid);
	build(right, mid+1, r);

	tree[Node].insert(tree[left].begin(), tree[left].end());
	tree[Node].insert(tree[right].begin(), tree[right].end());
	return;
}


// This query returns the smallest integer greater than or equal to this number in the range [i,j]
ll query(int Node, int l, int r, int i, int j, ll val)
{
	//cout << "Node: " << Node << " l: " << l << ",r: " << r << endl;
	if(l > r or r < i or j < l)
		return INF;

	if(i <= l and r <= j)
	{
		// We can look in this segment by doing a binary search
		multiset<ll> :: iterator it = tree[Node].lower_bound(val);
		if (it != tree[Node].end())
			return *it;

		return INF;
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

	return min(query(left, l, mid, i, j, val), query(right, mid+1, r, i, j, val));
}	

void update(int Node, int l, int r, int pos, ll new_val)
{
	tree[Node].erase(tree[Node].find(arr[pos]));
	tree[Node].insert(new_val);

	if(l != r)
	{
		int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

		if(pos <= mid)
			update(left, l, mid, pos, new_val);
		else
			update(right, mid+1, r, pos, new_val);
	}	
	else
		arr[pos] = new_val;

	return;
}

void solve()
{
	int N = read<int>(), M = read<int>();

	for(int i = 0; i < N; i++)
		arr[i] = read<ll>();

	build(1, 0, N-1);
	
	ll val;
	int x, y;
	for(int i = 0; i < M; i++)
	{
		x = read<int>(), y = read<int>(), val = read<ll>();
		x--, y--;

		cout << query(1, 0, N-1, x, y, val) << endl;
	}
	return;
}

int main()
{
	solve();
	return 0;
}

