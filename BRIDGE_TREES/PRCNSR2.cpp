
// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MXN 1010
#define INF 1000000007
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

int U[10*MXN], V[10*MXN];
vector< pair<int, int> > tree[MXN];	// Bridge-Tree
vector<int> gph[MXN];	// Given Graph
int IN[MXN], visited[MXN], T;
bool isBridge[10*MXN];
int cmpno, comp[MXN];
queue<int> Q[MXN];		// Different queue for each of the components
int f[MXN][MXN], ff[MXN][MXN];
int N, M, MOD;

int adj(int cur, int e)
{
	return (U[e] == cur) ? V[e] : U[e];
}

int dfs0(int node, int edge)		// Marks all the bridge edges
{
	visited[node] = true;
	IN[node] = T++;
	int dbe = IN[node];
	for(int i = 0; i < SZ(gph[node]); i++)
	{
		int e = gph[node][i];
		int w = adj(node, e);
		if(!visited[w])
			dbe = min(dbe, dfs0(w, e));
		else if(edge != e)
			dbe = min(dbe, IN[w]);
	}
	if(dbe == IN[node] and edge != -1)
		isBridge[edge] = true;
	return dbe;
}

void dfs1(int cur)
{
	int currcmp = cmpno; 	// Current component no
	Q[currcmp].push(cur);	// A different queue for each component
	visited[cur] = 1;

	while(!Q[currcmp].empty())
	{
		int u = Q[currcmp].front();
		Q[currcmp].pop();
		comp[u] = currcmp;

		for(int i = 0; i < SZ(gph[u]); i++)
		{
			int e = gph[u][i];
			int w = adj(u, e);
			if(visited[w])
				continue;

			// If the edge under consideration is bridge
			// and other side is not yet explored then do dfs

			if(isBridge[e])
			{
				cmpno++;
				tree[currcmp].PB(make_pair(cmpno, f[U[e]][V[e]]));
				tree[cmpno].PB(make_pair(currcmp, f[U[e]][V[e]]));
				dfs1(w);
			}
			else
			{
				Q[currcmp].push(w);
				visited[w] = 1;
			}
		}
	}
	return;
}

void build_tree()
{
	T = 0;
	cmpno = 0;
	SET(visited, 0);
	dfs0(1, -1);			// Find out all the bridges

	
	SET(visited, 0);
	dfs1(1);				// Now build the bridge tree
}

int rec(int i, int j)
{
	if(f[i][j] != -1) 	return f[i][j];

	if(i == j)	f[i][j] = f[j][i] = 0;
	else if(i == 1 or j == 1) f[i][j] = f[j][i] = 1;
	else	f[i][j] = f[j][i] = (rec(i-1, j) + rec(i, j-1)) % MOD + rec(i-1, j-1) % MOD;
	return f[i][j];
}

void res_calc()
{
	for(int i = 1; i <= N; i++) gph[i].clear(), tree[i].clear();

	for(int i = 1; i <= M; i++) isBridge[i] = false;

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			f[i][j] = -1, ff[i][j] = -1;

	for(int i = 1; i <= N; i++)
		for(int j = i+1; j <= N; j++)
			if(f[i][j] == -1)
				rec(i, j);

	return;
}

int root;

void dfs(int cur, int pre, int VAL)
{
	ff[root][cur] = VAL;
	for(int i = 0; i < tree[cur].size(); i++)
	{
		int child = tree[cur][i].first;
		int edge_cost = tree[cur][i].second;

		if(child != pre)
		{
			dfs(child, cur, min(VAL, edge_cost));
		}
	}
}

void process_tree()
{
	for(root = 0; root < cmpno; root++)
		dfs(root, root, INF);	
	return;
}

void solve()
{
	scanf("%d %d %d", &N, &M, &MOD);

	res_calc();

	for(int i = 0; i < M; i++)
	{
		scanf("%d %d", &U[i], &V[i]);
		gph[U[i]].PB(i);
		gph[V[i]].PB(i);
	}

	build_tree();
	//cout << cmpno << endl;

	process_tree();

	int ans = -1;
	for(int i = 1; i <= N; i++)
	{
		for(int j = i+1; j <= N; j++)
		{
			if(comp[i] == comp[j]) continue;

			ans = max(ans, f[i][j] - ff[comp[i]][comp[j]]);
		}
	}

	cout << ans << endl;

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