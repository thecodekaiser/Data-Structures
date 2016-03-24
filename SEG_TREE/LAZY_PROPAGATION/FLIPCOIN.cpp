// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 100100

struct node
{
	int heads, tails;
	bool lazy;
} tree[4 * MXN];

void build(int Node, int l, int r)
{
	if(l > r)
		return;
		
	if(l == r)
	{
		tree[Node].tails = 1;
		return;
	}
	
	build(2 * Node, l, (l+r)/2);
	build(2 * Node + 1, (l+r)/2 + 1, r);
	tree[Node].tails = tree[2 * Node].tails + tree[2 * Node + 1].tails;
	tree[Node].heads = (r - l + 1) - tree[Node].tails;
	return;
}

void update(int Node, int l, int r, int i, int j)
{
	if(tree[Node].lazy)
	{
		swap(tree[Node].tails, tree[Node].heads);
		
		if(l != r)
		{
			tree[2*Node].lazy   ^= 1;
			tree[2*Node+1].lazy ^= 1;
		}
		
		tree[Node].lazy ^= 1;
	}
	
	if(l > r or r < i or j < l) 
		return;
	
	if(i <= l and r <= j)
	{
		swap(tree[Node].tails, tree[Node].heads);
		
		if(l != r)
		{
			tree[2*Node].lazy   ^= 1;
			tree[2*Node+1].lazy ^= 1;
		}
		
		return;
	}
	
	update(2 * Node, l, (l+r)/2, i, j);
	update(2 * Node + 1, (l+r)/2 + 1, r, i, j);
	
	tree[Node].heads = tree[2 * Node].heads + tree[2 * Node + 1].heads;
	tree[Node].tails = (r - l + 1) - tree[Node].heads;
	return;
}

int query(int Node, int l, int r, int i, int j)
{
	if(tree[Node].lazy)
	{
		swap(tree[Node].tails, tree[Node].heads);
		
		if(l != r)
		{
			tree[2*Node].lazy   ^= 1;
			tree[2*Node+1].lazy ^= 1;
		}
		tree[Node].lazy ^= 1;
	}
	
	if(l > r or r < i or j < l) 
		return 0;
	
	if(i <= l and r <= j)
	{
		//cout << "HERE: " << l << "," << r << " " << tree[Node].heads << "," << tree[Node].tails << endl;
		return tree[Node].heads;
	}
	
	return query(2 * Node, l, (l+r)/2, i, j) + query(2 * Node + 1, (l+r)/2 + 1, r, i, j);
}

void solve()
{
	int N, Q, cmd, L, R;
	scanf("%d %d", &N, &Q);
	
	build(1, 0, N-1);

	for(int i = 0; i < Q; i++)
	{
		scanf("%d %d %d", &cmd, &L, &R);
		
		if(!cmd)
		{
			update(1, 0, N-1, L, R);
		}
		else
		{
			printf("%d\n", query(1, 0, N-1, L, R));
		}
	}
	
	
	return;
}

int main()
{
	solve();
	return 0;
}