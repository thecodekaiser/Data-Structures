// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 100100
#define INF (int)1e9+7

struct  Edge
{
	int from, to, cap, flow;
	Edge (int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
	ll rcap () { return cap - flow; }
};

int N, M, S, T, ptr[MXN], layer[MXN];
vector<int>  gph[MXN];
queue<int> Q;
vector<Edge> e;

void add_edge(int from, int to, int cap)
{
	Edge e1 = Edge(from, to, cap, 0);
	Edge e2 = Edge(to, from, 0, 0);
	gph[from].push_back((int) e.size());
	e.push_back(e1);
	gph[to].push_back((int) e.size());
	e.push_back(e2);
}

bool bfs()
{
	Q.push(S);
	memset(layer, -1, sizeof(layer));
	layer[S] = 0;

	while(!Q.empty())
	{
		int from = Q.front(); Q.pop();
		cout << "FROM: " << from << endl;

		for (size_t i = 0; i < gph[from].size(); i++)
		{
			int id = gph[from][i], to = e[id].to;
			if (layer[to] == -1 and e[id].flow < e[id].cap)
			{
				Q.push(to);
				layer[to] = layer[from] + 1;
			}
		}
	}

	return layer[T] != -1;
}

int dfs(int cur, int flow)
{
	if(!flow)		return 0;
	if(cur == T)	return flow;

	for (; ptr[cur] < gph[cur].size(); ptr[cur]++)
	{
		int id = gph[cur][ptr[cur]], to = e[id].to;
		if(layer[to] != layer[cur] + 1) 
			continue;

		int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
		if (pushed)
		{
			e[id].flow 	 += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
	}

	return 0;
}

int dinic()
{
	int flow = 0;
	for(;;)
	{
		if(!bfs())
			break;
		memset(ptr, 0, sizeof(ptr));
		while (int pushed = dfs(S, INF))
			flow += pushed;
	}

	return flow;
}

void solve()
{
	scanf("%d %d", &N, &M);

	int x, y, cap;

	for(int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &x, &y, &cap);
		x--, y--;
		add_edge(x, y, cap);
	}	

	scanf("%d %d", &S, &T);			// Source and Destination
	S--, T--;

	int mx_flow = dinic();

	printf("Max Flow in this situation is: %d\n", mx_flow);


	return;
}

int main()
{
	solve();
	return 0;
}