/**
 * This is the first question where I am going to use HLD
 * It simply requires us to give the max-weighted edge on the path b/w two nodes
 * Author: thecodekaiser
 */
 
#include <bits/stdc++.h>
using namespace std;
 
#define root 1
#define MXN 10010			// Max no of nodes in the tree
#define LVL 14
 
// Required things
vector<int> gph[MXN], idxx[MXN], costs[MXN];	// GPH -> Adjacency List, idxx -> Stores which node is connected to which node
						// costs -> Cost of ith edge from a node
 
int baseArray[MXN];			// Used to form the segment tree
int ptr;	
int chainNo, chainHead[MXN], posInBase[MXN], chainInd[MXN];		// Will be used for HLD
int depth[MXN], parent[LVL][MXN], otherEnd[MXN], subsize[MXN];		// Will be used during dfs and later to determine LCA
 
// My seg tree node
struct val
{
	int mx, mn;	// Max and min in segment
	
	// Constructor
	val() { mx = mn = -1; }	
} tree[MXN*6];			// Seg tree
 
// Merge Function
val merge(val A, val B)
{
	val res;
 
	if(A.mx == -1 and A.mn == A.mx)
	{
		res.mx = B.mx;
		res.mn = B.mn;
	}
	else if(B.mx == -1 and B.mn == B.mx)
	{
		res.mx = A.mx;
		res.mn = A.mn;
	}
	else
	{
		res.mx = max(A.mx, B.mx);
		res.mn = min(A.mn, B.mn);
	}
	return res;
}
		
 
 
// Construction of segtree: Uses baseArray for construction
void build_SEG(int Node, int l, int r)
{
	if(l == r)	
	{
		tree[Node].mx = tree[Node].mn = baseArray[l];
		return;
	}
 
	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	build_SEG(left, l, mid);
	build_SEG(right, mid+1, r);
 
	tree[Node] = merge(tree[left], tree[right]);
	return;
}
 
// Updatation of segtree: Point update..updates a single element
void update_SEG(int Node, int l, int r, int i, int val)
{
	if (l > i or i > r)
		return;
 
	if(i <= l and r <= i)
	{
		tree[Node].mx = tree[Node].mn = val;
		return;
	}
 
	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	update_SEG(left, l, mid, i, val);
	update_SEG(right, mid+1, r, i, val);
	tree[Node] = merge(tree[left], tree[right]);
	return;
}
 
// Query in the segtree: Given i and j it will return the max and min the range [i,j]
val query_SEG(int Node, int l, int r, int i, int j)
{
	if(l > r or i > r or j < l)
	{
		val v;
		return v;
	}
 
	if(i <= l and r <= j)
	{
		return tree[Node];
	}
 
	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	val v1 = query_SEG(left, l, mid, i, j);
	val v2 = query_SEG(right, mid+1, r, i, j);
 
	return merge(v1, v2);
}
 
 
/**
 * Actual HL-Decomposition: 
 * Initially we find the special child. Add it to current chain and call HLD on it
 * Then we form a new chain on each normal child of current node
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size.
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */
void HLD(int curNode, int cost, int prev)
{
	//cout << "curNode: " << curNode << " chainNo: " << chainNo << endl;
 
	if(chainHead[chainNo] == -1)
	{
		// Starting a new chain
		chainHead[chainNo] = curNode;	// Assign a chain head
	}
 
	chainInd[curNode]  = chainNo;		// This node belongs to chainNo chain
	posInBase[curNode] = ptr;		// We assign this place to curNode
	baseArray[ptr++]   = cost;		// We have now given this place to it
 
	cout << "curNode: " << curNode << " chainInd[curNode]: " << chainInd[curNode] << " posInBase[curNode]: " << posInBase[curNode] << " baseArrapy[ptr]: " << cost << endl;
	
	int sc = -1, ncost;	// sc -> Special Child
	for(int i = 0; i < gph[curNode].size(); i++)
	{
		if(gph[curNode][i] != prev)
		{
			if(sc == -1 || subsize[sc] < subsize[gph[curNode][i]])
			{
				sc = gph[curNode][i];
				ncost = costs[curNode][i];
			}
		}
	}
 
	if(sc != -1)	
	{
		// We have found a special child
		HLD(sc, ncost, curNode);
	}
			
	// Now form a new chain from each of the normal children
	for(int i = 0; i < gph[curNode].size(); i++)
	{
		if(gph[curNode][i] != prev)
		{
			if(sc != gph[curNode][i])
			{
				chainNo++;
				HLD(gph[curNode][i], costs[curNode][i], curNode);
			}
		}
	}
 
	return;
}
 
// LCA: Given two nodes u and v it returns their LCA
int LCA(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);	// We want v to be the higher one so it's depth will be lower
	int diff = depth[u] - depth[v];
 
	for(int i = 0; i < LVL; i++) if((diff >> i) & 1) u = parent[i][u];
	
	if(u == v)
		return u;
 
	for(int i = LVL-1; i >= 0; i--)
	{	
		if(parent[i][u] != parent[i][v])
		{
			u = parent[i][u]; v = parent[i][v];	// We bring both of them up
		}
	}
 
	return parent[0][u];
}
 
// query_up: This is the most important function
int query_up(int u, int v)
{
	if(u == v) return 0;		// Base case
	int uchain, vchain = chainInd[v], ans = -1;
	val vc;
	cout << "v: " << v << " chainInd[v]: " << chainInd[v] << endl;
 
	// uchain and vchain are chainNumbers of u and v
	while(1)
	{
		uchain = chainInd[u];
		cout << "uchain: " << uchain << " vchain: " << vchain << " vc.mx: " << vc.mx << endl;

		if(uchain == vchain)
		{
			// Both u and v are in the same chain .. update ans and then break
			if(u == v) break;
 
			vc = query_SEG(1, 0, ptr-1, posInBase[v], posInBase[u]);	// pos of v will always be lower since it is the LCA			
			cout << "posInBase[v]: " << posInBase[v] << " posInBase[u]: " << posInBase[u] << " vc.mx: " << vc.mx << endl;
			if(vc.mx > ans)
				ans = vc.mx;
			break;
		}

		vc = query_SEG(1, 0, ptr-1, posInBase[chainHead[uchain]], posInBase[u]);
 		cout << "posInBase[chainHead[uchain]]: "  << posInBase[chainHead[uchain]] << " posInBase[u]: " << posInBase[u] << " vc.mx: " << vc.mx << endl;

		// We are propagating upwards
		if(vc.mx > ans) ans = vc.mx;
		u = chainHead[uchain];	// Now we are going to chain head
		u = parent[0][u];	// Now we are going to another chain
	}
 
	return ans;
}
 
// Query: Print the max edge on path from u to v
void query(int u, int v)
{
	// Break the path from u to v in u -> LCA(u,v) , LCA(u,v) -> v
	int lca = LCA(u, v);
	cout << "u: " << u << " v: " << v << " lca: " << lca << endl;
	cout << "chainInd[u]: " << chainInd[u] << " chainInd[v]: " << chainInd[v] << " chainInd[lca]: " << chainInd[lca] << endl;
 
	int ans = query_up(u, lca);
	int temp = query_up(v, lca);
	
	ans = max(ans, temp);
	printf("%d\n",ans);
	cout << endl;
	return;
}
 
// Change: Change the cost of the ith edge 
void change(int i, int val)
{
	int u = otherEnd[i];	// Find the node and then change its value in segtree
	update_SEG(1, 0, ptr-1, posInBase[u], val);
	return;
}
 
// DFS: Used to set the depth, parent, subtree_size of each node
void dfs(int cur, int prev, int dpt = 0)
{
	parent[0][cur] = prev;		// Set immediate ancestor
	depth[cur] = dpt;		// Set depth of this node
	subsize[cur] = 1;		// Currently set the size as 1
 
	for(int i = 0; i < gph[cur].size(); i++)	
	{
		if(gph[cur][i] != prev)
		{
			otherEnd[idxx[cur][i]] = gph[cur][i];	// Setting edge end
			dfs(gph[cur][i], cur, dpt+1);
			subsize[cur] += subsize[gph[cur][i]];
		}
	}	
	return;
}
 
void solve()
{
	int N;
	scanf("%d",&N);
	
	// Reinitialize everything
	ptr = 0;
	for(int i = 1; i <= N; i++)
	{
		gph[i].clear();
		costs[i].clear();
		idxx[i].clear();
		chainHead[i] = -1;
 
		for(int j = 0; j < LVL; j++) 
			parent[j][i] = -1;
	}
 
	int x, y, cost;
	// Reading in the edges
	for(int i = 1; i <= N-1; i++)
	{
		scanf("%d %d %d", &x, &y, &cost);
 
		gph[x].push_back(y);
		costs[x].push_back(cost);
		idxx[x].push_back(i);
		gph[y].push_back(x);
		costs[y].push_back(cost);
		idxx[y].push_back(i);		
	}
 
	//cout << "HERE" << endl;
 
	chainNo = 0;		// Set it to 0
	dfs(root, -1);		// We set subsize, parent, depth during dfs
	
	//cout << "HERE" << endl;
	HLD(root, -1, -1);	// DO a HLD
 
	//cout << "HERE" << endl;
 
	build_SEG(1, 0, ptr);	// Now make the seg tree
 
	// Dynamic programming for LCA
	for(int i = 1; i < LVL; i++)
		for(int j = 1; j <= N; j++)
			if(parent[i-1][j] != -1)
				parent[i][j] = parent[i-1][parent[i-1][j]];
 

	cout << "THIS IS THE BASE ARRAY:\n";
	for(int i = 0; i < ptr; i++)
		cout << baseArray[i] << " ";
	cout << endl;
	cout << endl;
	
	while(1) 
	{
		char s[100];
		scanf("%s", s);
		if(s[0]=='D')
		{
			break;
		}
 
		int a, b;
		scanf("%d %d", &a, &b);
 
		if(s[0]=='Q')
		{
			query(a, b);
		}
		else 
		{
			change(a, b);
		}
	}
		
	return;
}
 
int main()
{
	int t;
	cin >> t;
	while(t--)
		solve();
	return 0;
}
