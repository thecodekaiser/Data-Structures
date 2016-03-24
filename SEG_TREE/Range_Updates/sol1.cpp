// This is one of my favorites
// Because here we are doing range updates and range queries on segment tree
// Each node will basically store the sum on it and how much should it propogate down to its subtree
#include <iostream>
#include <cstdlib>
#include <cstdio>
 
using namespace std;
typedef long long ll;
 
// In this segment tree it will basically store the sum of intervals
 
ll combine(ll L, ll R)
{	return L + R;	}
 
template <typename T> class SEG {
 
private:
	ll * tree;
	int len;
 
	// Builder function 
	void build(int Node, int l, int r)
	{
		if(l == r)	// It's a leaf node
		{
			tree[Node] = 0;
		}
		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
 
			build(left, l, mid);
			build(right, mid+1, r);
 
			tree[Node] = combine(tree[left], tree[right]);
		}
	}
 
	// Update operation
	void update(int Node, int l, int r, int i, int j, ll val)
	{
		//cout << "NODE: " << Node << " L: " << l+1 << " R: " << r+1 << " I: " << i+1 << " J: " << j+1 << " Val: " << val << endl;
 
		if(i > r || j < l)	return;
 
		if(l == r)
			tree[Node] += val;// cout << "UPDATED: " << l+1 << endl;
		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
 
			update(left, l, mid, i, j, val);
			update(right, mid+1, r, i, j, val);
 
			tree[Node] = combine(tree[left], tree[right]);
		}
	}
 
	// Query
	ll query(int Node, int l, int r, int i, int j)
	{
	//	cout << "Node: " << Node << " L: " << l << " R: " << r << " I: " << i << " J: " << j << endl;
		if(i > r || j < l) 	return 0;
 
		else if(i <= l and j >= r)
			{/*cout << "RETURNING: " << Node << endl;*/ return tree[Node];}
		else
		{
			int p1, p2;
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
 
 
			p1 = query(left, l, mid, i, j);
			p2 = query(right, mid+1, r , i, j);
 
			return	combine(p1,p2);
		}
	}
 
public:
	// Constructor
	SEG(int N)
	{
		len = N;
		tree = (ll *) malloc (4 * len * sizeof(ll));
 
		build(1, 0, len-1);
 
	//	for(int i = 1; i <= 15; i++)
	//		cout << i << " " << tree[i] << endl;
 
	}
 
	// Update 
	void update(int i, int j, ll val)
	{	
		//cout << "I: " << i << " J: " << j << " VAL: " << val << endl;
		update(1, 0, len-1, i, j, val);
	//	for(int i = 1; i <= 15; i++)
	//		cout << i << " " << tree[i] << endl;
	}
 
	// Query
	ll query(int i, int j)
	{
		return query(1, 0, len-1, i, j);
	}
};
 
void solve()
{
	int N, Q, cmd, p, q;
	ll val;
	scanf("%d %d",&N, &Q);
 
	SEG<int> st = SEG<int>(N);
 
	for(int i = 0; i < Q; i++)
	{
		scanf("%d",&cmd);
		if(cmd == 0)
		{
			scanf("%d %d %lld",&p, &q, &val);
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
