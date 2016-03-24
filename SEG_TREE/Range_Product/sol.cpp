// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 1000

ll tree[4*MAXN];

void build(int Node, int l, int r)
{
	if(l == r)
	{
		tree[Node] = 1;
		return;
	}

	int left = 2 * Node, right = 2 * Node+1, mid = (l+r)/2;
	build(left, l, mid);
	build(right, mid+1, r);
	tree[Node] = tree[left]*tree[right];
}

void update(int Node, int l, int r, int i, int val, int M)
{
	if(l == r)
	{	tree[Node] = val; return;	}
	else
	{
		int left = 2 * Node, right = 2 * Node+1, mid = (l+r)/2;
		if(i <= mid)
			update(left, l, mid, i, val, M);
		else
			update(right, mid+1, r, i, val, M);
		tree[Node] = (tree[left] * tree[right]) % M;
	}
}

ll query(int Node, int l, int r, int i, int j, int M)
{
	if(l > r or i > r or j < l)
		return 1;

	if(i <= l and r <= j)
		return tree[Node];

	int left = 2 * Node, right = 2 * Node+1, mid = (l+r)/2;
	ll val1 = query(left, l, mid, i, j, M);
	ll val2 = query(right, mid+1, r, i, j, M);
	return (val1 * val2) % M;
}

void solve()
{
	int N, M, Q, L, R;
	cin >> N >> M;
	build(1, 1, N);
	cout << "BUILT" << endl;
	ll ptr[N+1];
	for(int i = 1; i <= N; i++)
	{
		cin >> ptr[i];
		cout << ptr[i] << " ";
		update(1, 1, N, i, ptr[i], M);
	}

	cout << "DONE" << endl;
	cin >> Q;
	for(int i = 0; i < Q; i++)
	{
		cin >> L >> R;
		cout << query(1, 1, N, L, R, M) << endl;
	}
	return;
}

int main()
{
	solve();

	return 0;
}
