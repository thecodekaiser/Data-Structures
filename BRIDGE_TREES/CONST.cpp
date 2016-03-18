// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MXN 100100
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

int U[4*MXN], V[4*MXN];
vector<int> tree[MXN];	// Bridge-Tree
vector<int> gph[MXN];	// Given Graph
int IN[MXN], visited[MXN], T;
bool isBridge[4*MXN];
int cmpno, comp[MXN];
queue<int> Q[MXN];		// Different queue for each of the components
int ans[MXN];			// How many different nodes can be visited from comp[i] = ans[i]
int compSize[MXN];		// No of nodes in this component

int N, M, P;

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
				tree[currcmp].PB(cmpno);
				tree[cmpno].PB(currcmp);
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

	for(int i = 1; i <= N; i++)
		compSize[comp[i]]++;
}

int par[MXN];
int cnt[MXN][17];

void dfs0_0(int cur, int pre)
{
	par[cur] = pre;

	for(int i = 0; i < tree[cur].size(); i++)
	{
		if(tree[cur][i] != pre)
			dfs0_0(tree[cur][i], cur);
	}

	int lvl = 0, cc = cur;

	while(lvl <= P and cc != -1)
	{
		cnt[cc][lvl] += compSize[cur];
		lvl += 1;
		cc = par[cc];
	}
}

int temp[17];

void dfs0_1(int cur, int pre)
{
	par[cur] = pre;
	//cout << "cur: " << cur << " pre: " << pre << endl;

	for(int i = 0; i < tree[cur].size(); i++)
	{
		if(tree[cur][i] != pre)
		{
			temp[0] = 0;
			for(int p = 0; p + 1 <= P; p++)
			{
				if(!p)
					temp[p+1] = cnt[cur][p];
				else
					temp[p+1] = cnt[cur][p] - cnt[tree[cur][i]][p-1];
			}

			for(int p = 0; p <= P; p++)
			{
				cnt[tree[cur][i]][p] += temp[p];
			}

			dfs0_1(tree[cur][i], cur);
		}
	}
}

void process_tree()
{
	cmpno++;
	dfs0_0(0, -1);
	
	dfs0_1(0, -1);

	for(int i = 0; i < cmpno; i++)
	{
		for(int p = 0; p <= P; p++)
		{
			ans[i] += cnt[i][p];
		}
	}
	
	return;
}

void solve()
{
	scanf("%d %d %d", &N, &M, &P);

	for(int i = 0; i < M; i++)
	{
		scanf("%d %d", &U[i], &V[i]);
		gph[U[i]].PB(i);
		gph[V[i]].PB(i);
	}

	build_tree();
	process_tree();

	for(int i = 1; i <= N; i++)
		printf("%d\n", ans[comp[i]] - 1);

	return;
}



int main()
{
	solve();
	return 0;
}