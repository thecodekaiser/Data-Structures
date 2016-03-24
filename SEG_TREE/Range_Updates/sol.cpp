// Author: thecodekaiser
// This is one of my favorites
// Because here we are doing range updates and range queries on segment tree
// Each node will basically store the sum on it and how much should it propogate down to its subtree
// This one has incorporated lazy updates
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
typedef long long ll;

ll combine(ll A, ll B)	{ return A+B; }

class SEG {

private:
	ll * tree;
	ll * lazy;
	int len;

	// Build
	void build(int Node, int l, int r)
	{
		if(l == r)
		{
			tree[Node] = 0;
			lazy[Node] = 0;
		}

		else
		{
			int Left = 2 * Node, Right = 2 * Node + 1, mid = (l+r)/2;
			build(Left, l, mid);
			build(Right, mid+1, r);
			
			tree[Node] = combine(tree[Left], tree[Right]);	
		}
	}


	// Update operation to a range [i,j]
	void update(int Node, int l, int r, int i, int j, ll val)
	{
		int Left = 2 * Node, Right = 2 * Node + 1, mid = (l+r)/2;

		if(i > r || j < l)
		{
		//	cout << "1 " ; 
		//	cout << "NODE: " << Node << " tree[Node]: " << tree[Node] << endl;
			return;
		}

		if(l == r)
		{
			tree[Node] += val;
			if(lazy[Node] != 0)
			{
				tree[Node] += lazy[Node];
				lazy[Node]  = 0;
			}
		//	cout << "2 " ;
		//	cout << "NODE: " << Node << " tree[Node]: " << tree[Node] << endl;
			return;
		}

		if(i <= l and r <= j)
		{
			tree[Node] += (val * (r - l + 1));

			if(l != r)
			{	
				// If not a leaf node
				lazy[Left] += val;
				lazy[Right] += val;
			}
		//	cout << "3 " ;
		//	cout << "NODE: " << Node << " tree[Node]: " << tree[Node] << endl;
			return;
		}


		else if	(i <= r and j > r)	
			tree[Node] += (val * (r-i+1));
		else if	(l <= j and l > i)
			tree[Node] += (val * (j-l+1)); 
		else if	(l <= i and j <= r)
			tree[Node] += (val * (j-i+1));
		

		update(Left, l, mid, i, j, val);
		update(Right, mid+1, r, i, j, val);

//		tree[Node] = combine(tree[Left], tree[Right]);
//		cout << "4 " ;
//		cout << "NODE: " << Node << " tree[Node]: " << tree[Node] << endl;
	}

	// Query
	ll query(int Node, int l, int r, int i, int j)
	{
		//cout << "NODE: " << Node << " L: " << l << " R: " << r << " I: " << i << " J: " << j << endl;
		if(i > r || j < l || i > j)	return 0;

		int Left = 2 * Node, Right = 2 * Node + 1, mid = (l+r)/2;
	
		if(lazy[Node] != 0)		// This node needs to be updated
		{
			tree[Node] += (lazy[Node] * (r - l + 1));
			// Propogate downwards if not a leaf node
			if(l != r)
			{
				lazy[Left] += lazy[Node];
				lazy[Right] += lazy[Node];
			}
			lazy[Node] = 0;		// Reset it
		}

		if(i <= l and r <= j)	return tree[Node];

		ll q1 = query(Left, l, mid, i, j);
		ll q2 = query(Right, mid+1, r, i, j);

		return combine(q1,q2);
	}

			
public:
	// Constructor
	SEG(int N)
	{
		len = N;
		tree = (ll *) malloc (len*4 * sizeof(ll));	
		lazy = (ll *) malloc (len*4 * sizeof(ll));

		build(1, 0, len-1);

	//	for(int i = 1; i <= 15; i++)
	//		cout << i << " " << tree[i] << endl;
	}


	// Update
	void update(int i, int j, ll val)
	{
		update(1, 0, len-1, i, j, val);
	
/*
		for(int i = 1; i <= 15; i++)
			cout << i << " " << tree[i] << endl;
		for(int i = 1; i <= 15; i++)
			cout << i << " " << lazy[i] << endl;
*/
	
	}

	// Query
	ll query(int i, int j)
	{
		ll val = query(1, 0, len-1, i, j);
	/*
		for(int i = 1; i <= 15; i++)
			cout << i << " " << tree[i] << endl;
		for(int i = 1; i <= 15; i++)
			cout << i << " " << lazy[i] << endl;
	*/
		return val;
	}

};


void solve()
{
	int N, Q, cmd, p, q;
	ll val;
	scanf("%d %d",&N, &Q);
 
	SEG st = SEG(N);
 
	for(int i = 0; i < Q; i++)
	{
		scanf("%d",&cmd);
		if(cmd == 0)
		{
			scanf("%d %d %lld",&p, &q, &val);
			//cout << p << " " << q << val << endl;
			st.update(p-1,q-1,val);
		}
		else
		{
			scanf("%d %d",&p, &q);
			printf("%lld\n",st.query(p-1,q-1));
		}
	}
 
	return;
}
 
int main()
{
	int t;	
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
