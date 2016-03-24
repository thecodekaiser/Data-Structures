// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

/**
 * This code finds the smallest integer greater than or equal to a given integer in a given range.
 * It does not allow modification requests.
 * It is implemented using the merge-sort tree.
 */

#define MXN 100010
#define INF 1000000007
#define GETC getchar_unlocked()

typedef long long ll;

vector<ll> tree[4*MXN];		// This is the mergesort tree
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
		tree[Node].push_back(arr[l]);
		return;
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

	build(left, l, mid);
	build(right, mid+1, r);

	merge(tree[left].begin(), tree[left].end(), tree[right].begin(), tree[right].end(), back_inserter(tree[Node]));
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
		int lo = 0, hi = tree[Node].size()-1;
		int mid;
		while(lo < hi)
		{
			mid = (lo+hi)>>1;

			if(tree[Node][mid] >= val)
				hi = mid;
			else
				lo = mid+1;
		}

		return tree[Node][lo];
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

	return min(query(left, l, mid, i, j, val), query(right, mid+1, r, i, j, val));
}	

void solve()
{
	int N = read<int>(), M = read<int>();

	for(int i = 0; i < N; i++)
		arr[i] = read<ll>();

	build(1, 0, N-1);
	//cout << "BUILT" << endl;
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

