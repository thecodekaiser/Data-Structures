/**
 * This is the first question where I am going to use HLD
 * It simply requires us to give the max-weighted edge on the path b/w two nodes
 * Author: thecodekaiser
 */
 
#include <bits/stdc++.h>
using namespace std;
 
#define root 0
#define MXN 10010			// Max no of nodes in the tree
#define LVL 14
 
// Required things
vector<int> gph[MXN], idxx[MXN], costs[MXN];	// GPH -> Adjacency List, idxx -> Stores which node is connected to which node
						// costs -> Cost of ith edge from a node
 
int baseArray[MXN];			// Used to form the segment tree
int ptr;	
int chainNo, chainHead[MXN], posInBase[MXN], chainInd[MXN];		// Will be used for HLD
int depth[MXN], parent[LVL][MXN], otherEnd[MXN], subsize[MXN];		// Will be used during dfs and later to determine LCA
 
int st[MXN*6], qt[MXN*6];

/*
 * make_tree:
 * Used to construct the segment tree. It uses the baseArray for construction
 */
void make_tree(int cur, int s, int e) {
	if(s == e-1) {
		st[cur] = baseArray[s];
		return;
	}
	int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
	make_tree(c1, s, m);
	make_tree(c2, m, e);
	st[cur] = st[c1] > st[c2] ? st[c1] : st[c2];
}

/*
 * update_tree:
 * Point update. Update a single element of the segment tree.
 */
void update_tree(int cur, int s, int e, int x, int val) {
	if(s > x || e <= x) return;
	if(s == x && s == e-1) {
		st[cur] = val;
		return;
	}
	int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
	update_tree(c1, s, m, x, val);
	update_tree(c2, m, e, x, val);
	st[cur] = st[c1] > st[c2] ? st[c1] : st[c2];
}

/*
 * query_tree:
 * Given S and E, it will return the maximum value in the range [S,E)
 */
void query_tree(int cur, int s, int e, int S, int E) {
	if(s >= E || e <= S) {
		qt[cur] = -1;
		return;
	}
	if(s >= S && e <= E) {
		qt[cur] = st[cur];
		return;
	}
	int c1 = (cur<<1), c2 = c1 | 1, m = (s+e)>>1;
	query_tree(c1, s, m, S, E);
	query_tree(c2, m, e, S, E);
	qt[cur] = qt[c1] > qt[c2] ? qt[c1] : qt[c2];
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
 
	cout << "curNode: " << curNode+1 << "  chainInd[curNode]: " << chainInd[curNode] << " posInBase[curNode]: " << posInBase[curNode] << " baseArrapy[ptr]: " << cost << endl;
	
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
	
	cout << "v: " << v << " chainInd[v]: " << chainInd[v] << endl;
 
	// uchain and vchain are chainNumbers of u and v
	while(1)
	{
		uchain = chainInd[u];
		cout << "uchain: " << uchain << " vchain: " << vchain << " ans: " << ans << endl;

		if(uchain == vchain)
		{
			// Both u and v are in the same chain .. update ans and then break
			if(u == v) break;
 
			query_tree(1, 0, ptr, posInBase[v]+1, posInBase[u]+1);	// pos of v will always be lower since it is the LCA
			cout << "posInBase[v]: " << posInBase[v] << " posInBase[u]: " << posInBase[u] << " qt[1]: " << qt[1] << endl;

			if(qt[1] > ans)
				ans = qt[1];
			break;
		}
 
		query_tree(1, 0, ptr, posInBase[chainHead[uchain]], posInBase[u]+1);
		cout << "posInBase[chainHead[uchain]]: "  << posInBase[chainHead[uchain]] << " posInBase[u]: " << posInBase[u] << " qt[1]: " << qt[1] << endl;

		// We are propagating upwards
		if(qt[1] > ans) ans = qt[1];
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
	update_tree(1, 0, ptr, posInBase[u], val);
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
	for(int i = 0; i < N; i++)
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
	for(int i = 1; i < N; i++)
	{
		scanf("%d %d %d", &x, &y, &cost);
 		x--, y--;

		gph[x].push_back(y);
		costs[x].push_back(cost);
		idxx[x].push_back(i-1);
		gph[y].push_back(x);
		costs[y].push_back(cost);
		idxx[y].push_back(i-1);		
	}
 
	//cout << "HERE" << endl;
 
	chainNo = 0;		// Set it to 0
	dfs(root, -1);		// We set subsize, parent, depth during dfs
	
	//cout << "HERE" << endl;
	HLD(root, -1, -1);	// DO a HLD
 
	//cout << "HERE" << endl;
 
	make_tree(1, 0, ptr);	// Now make the seg tree
 
	// Dynamic programming for LCA
	for(int i = 1; i < LVL; i++)
		for(int j = 0; j < N; j++)
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
			query(a-1, b-1);
		}
		else 
		{
			change(a-1, b);
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
 

