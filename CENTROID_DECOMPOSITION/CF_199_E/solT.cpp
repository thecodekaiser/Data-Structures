#include<bits/stdc++.h>

using namespace std;


const int N = int(1e5)+10;
const int LVL= 20;
const int INF = int(1e9);
set<int> gph[N];
int par[N],sub[N],depth[N],ans[N];
int DP[LVL][N];
int n,m;

/*Using centroid Decomposition of a tree */

/*----------- Pre-Processing ------------*/
void dfs(int cur, int pre)
{
	for(auto it = gph[cur].begin(); it != gph[cur].end(); it++)
	{
		if(*it != pre)
		{
			DP[0][*it] = cur;
			depth[*it] = depth[cur] + 1;
			dfs(*it, cur);
		}
	}
}

void pre()
{
	depth[0] = 0;
	DP[0][0] = 1;
	dfs(0, -1);

	for(int i = 1; i < LVL; i++)
		for(int j = 0; j < N; j++)
			DP[i][j] = DP[i-1][DP[i-1][j]];

	return;
}

int lca(int a, int b)
{
	if(depth[a] > depth[b])
		swap(a, b);

	int diff = depth[b] - depth[a];

	for(int i = 0; i < LVL; i++)
		if(diff & (1 << i))
			b = DP[i][b];

	if(a == b) return a;

	for(int i = LVL-1; i >= 0; i--)
		if (DP[i][a] != DP[i][b])
			a = DP[i][a], b = DP[i][b];


	return DP[0][a];
}

int dist(int a, int b)
{
	return depth[a] + depth[b] - 2*depth[lca(a,b)];
}
/*-----------------Decomposition Part--------------------------*/
int nn;
void dfs1(int root, int pre)
{
	sub[root] = 1;
	nn++;
	for(auto it = gph[root].begin(); it != gph[root].end(); it++)
	{
		if(*it != pre)
		{
			dfs1(*it, root);
			sub[root] += sub[*it];
		}
	}
}

int dfs2(int root, int pre)
{
	for(auto it = gph[root].begin(); it != gph[root].end(); it++)
	{
		if(*it != pre and sub[*it] > nn/2)
			return dfs2(*it, root);
	}

	return root;
}

void decompose(int root,int p)
{
	nn=0;
	dfs1(root,root);
	int centroid = dfs2(root,root);
	if(p==-1)p=centroid;
	par[centroid]=p;
	for(auto it=gph[centroid].begin();it!=gph[centroid].end();it++)
	{
		gph[*it].erase(centroid);
		decompose(*it,centroid);
	}
	gph[centroid].clear();
}
/*----------------- Handle the Queries -----------------*/


void update(int Node)
{
	int x = Node;
	while(1)
	{
		ans[x] = min(ans[x], dist(x, Node));
		if(par[x] == x)	break;
		x = par[x];
	}
}

int query(int Node)
{
	int ret = INF;
	int x   = Node;

	while(1)
	{
		ret = min(ret, ans[x] + dist(x, Node));
		if(x == par[x]) break;

		x = par[x];
	}
	return ret;
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		gph[u-1].insert(v-1);
		gph[v-1].insert(u-1);
	}
	pre();
	decompose(0,-1);
	for(int i=0;i<n;i++)
		ans[i]=INF;
	update(0);//first node is initially painted red
	while(m--)
	{
		int t,v;
		scanf("%d %d",&t,&v);v--;
		if(t==1)
			update(v);
		else
			printf("%d\n", query(v));
	}
	return 0;
}