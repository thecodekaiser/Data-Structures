// Author: thecodekaiser
// This code uses Edmonds-Karp Algorithm(uses BFS to find Augmenting path) to implement Ford-Fulkerson algo

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 5005
#define INF (ll)1e9+7

struct Edge
{
	int from, to;
	ll cap, flow;
	Edge (int from, int to, ll cap, ll flow) : from(from), to(to), cap(cap), flow(flow) {}
};

vector<Edge> e;
vector<int> gph[MXN];
int N, M, S, D;
int from[MXN];
bool vis[MXN];

void add_edge(int from, int to, ll cap)
{
	Edge e1 = Edge(from, to, cap, 0LL);
	Edge e2 = Edge(to, from, 0LL, 0LL);
	gph[from].push_back((int) e.size());
	e.push_back(e1);
	gph[to].push_back((int) e.size());
	e.push_back(e2);
}

ll bfs()
{
	memset(from, -1, sizeof(from));
	memset(vis, false, sizeof(vis));

	queue<int> Q;
	Q.push(S);
	vis[S] = true;

	while(!Q.empty())
	{
		int cur = Q.front(); Q.pop();

		if(cur == D)
			break;		// We have reached the destination node

		for(int i = 0; i < gph[cur].size(); i++)
		{
			int id = gph[cur][i];
			int to = e[id].to;

			if(!vis[to] and e[id].flow < e[id].cap)
			{
				vis[to] = true;
				from[to] = id;		// Used this edge
				Q.push(to);
			}
		}

	}

	int where = D, id;
	ll path_cap = INF;
	while(from[where] > -1)
	{
		id = from[where];
		path_cap = min(path_cap, e[id].cap - e[id].flow);
		where = e[id].from;
	}

	where = D;
	while(from[where] > -1)
	{
		id = from[where];
		e[id].flow   += path_cap;
		e[id^1].flow -= path_cap;
		where = e[id].from;
	}

	if(path_cap == INF)
		return 0LL;
	else
		return path_cap;
}


void solve()
{
	scanf("%d %d", &N, &M);

	S = 1, D = N;
	int x, y;
	ll wt;
	for(int i = 0; i < M; i++)
	{
		scanf("%d %d %lld", &x, &y, &wt);
		add_edge(x, y, wt);		// Edge from x to y with weight = wt
	}

	ll mx_flow = 0;

	while(true)
	{
		ll cur_path_capacity = bfs();
		if(cur_path_capacity == 0LL)
			break;
		else
			mx_flow += cur_path_capacity;
	}
	//cout << "Max Flow from source to destination in this network is " << mx_flow << "\n";
	cout << mx_flow << "\n";
	return;
}

int main()
{
	solve();
	return 0;
}