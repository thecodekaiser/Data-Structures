// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define INF 1000000007
#define MXN 100005
#define LVL 20

set<int> gph[MXN];
int par[MXN], DP[LVL][MXN], depth[MXN], sub[MXN], ans[MXN];
int N, Q, t, u, v;

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
    depth[1] = 0;
    DP[0][1] = 1;
    dfs(1, -1);

    for(int i = 1; i < LVL; i++)
        for(int j = 1; j <= N; j++)
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


int cnt;

void dfs1(int root, int pre)
{
	sub[root] = 1;
	cnt++;
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
		if(*it != pre and sub[*it] > cnt/2)
			return dfs2(*it, root);
	}
 
	return root;
}

void decompose(int root,int pre)
{
	cnt = 0;
	dfs1(root,root);
	int cen = dfs2(root,root);
	
	if(pre == -1) pre = cen;
	par[cen] = pre;
	
	for(auto it = gph[cen].begin(); it != gph[cen].end(); it++)
	{
		gph[*it].erase(cen);
		decompose(*it, cen);
	}
	gph[cen].clear();
}

void update(int Node)
{
    int x = Node;
    while(1)
    {
        ans[x] = min(ans[x], dist(x, Node));
        if(par[x] == x) break;
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

void solve()
{
    cin >> N >> Q;

    for(int i = 0; i < N-1; i++)
    {
        scanf("%d %d", &v, &u);
        gph[u].insert(v);
        gph[v].insert(u);
    }

    pre();
    decompose(1, -1);

    for(int i = 1; i <= N; i++)
        ans[i] = INF;

    update(1);      // Paint node 1 red
    //cout << ans[1] << endl;

    for(int i = 0; i < Q; i++)
    {
        scanf("%d %d", &t, &v);


        if(t == 1)
            update(v);
        else
            printf("%d\n", query(v));

//      cout << lca(t,v) << " " << dist(t, v) << endl;

    }

    return;
}

int main()
{
    solve();
    return 0;
}