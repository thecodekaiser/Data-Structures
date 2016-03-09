// Author: thecodekaiser
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
typedef long long ll;
#define MAXN 1000005


ll combine(ll A, ll B)
{
	ll res;
	res = A + B;
	return res;
}

class SEG {

private:
	//ll * copyArr;
	ll * tree;
	int len;

	// Build
	void build(int Node, int l, int r)
	{
		if(l == r)
			tree[Node] = 0;

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

			build(left, l, mid);
			build(right, mid+1, r);

			tree[Node] = combine(tree[left], tree[right]);
		}
	}

	// Updation
	void update(int Node, int l, int r, int i, int val)
	{
		if(l == r)
			tree[Node] += (val);

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	
			if(i <= mid)
				update(left, l, mid, i, val);
			else
				update(right, mid+1, r, i, val);

			tree[Node] = combine(tree[left], tree[right]);
		}
	}

	ll query(int Node, int l, int r, int i, int j)
	{
		if(i > r || j < l)	return 0;

		else if(i <= l and j >= r) return tree[Node];

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

			return combine(query(left, l, mid, i, j), query(right, mid+1, r, i, j));
		}
	}

public: 	
	// Constructor
	SEG()
	{
		len = MAXN;
	//	copyArr = (ll *) malloc (len * sizeof(ll));
		tree    = (ll *) malloc (4*len * sizeof(ll));

		//for(int i = 0; i < len; i++)	copyArr[i] = 0;

		build(1, 0, len-1);
	}

	// Updation
	void update(int i, int val)
	{
		//copyArr[i] += val;
		update(1, 0, len-1, i, val);
		
	}

	// Query
	ll query(int i)
	{
		ll ans = query(1, 0, len-1,0,i);
		return ans;
	}
	
};

void solve()
{
	int N;
	scanf("%d",&N);
	
	SEG st;
	ll ans = 0, val;
	for(int i = 0; i < N; i++)
	{
	
		scanf("%lld",&val);
		if(val != 0)
		{	
			ans += st.query(val-1);	
		//	printf("%lld ", ans);
			st.update(val,val);
		}	
	}

	printf("%lld\n",ans);
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
