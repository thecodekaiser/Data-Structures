// Author: thecodekaiser
// This code uses Edmonds-Karp Algorithm(uses BFS to find Augmenting path) to implement Ford-Fulkerson algo

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 105
#define INF (int)1e9+7

int gph[MXN][MXN];	// Given graph
int rgph[MXN][MXN];					// Residual Network
int N, M, S, D;
int from[MXN];
bool vis[MXN];

int bfs()
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

		for(int i = 0; i < N; i++)
		{
			int adj = i;

			if(!vis[adj] and rgph[cur][adj] > 0)
			{
				vis[adj] = true;
				from[adj] = cur;
				Q.push(adj);
			}
		}

	}

	int where = D, prev, path_cap = INF;
	while(from[where] > -1)
	{
		prev = from[where];
		//cout << "Prev: " << prev << " where: " << where << endl;

		path_cap = min(path_cap, rgph[prev][where]);
		where = prev;
	}

	where = D;
	while(from[where] > -1)
	{
		prev = from[where];
		rgph[prev][where] -= path_cap;
		rgph[where][prev] += path_cap;
		where = prev;
	}

	if(path_cap == INF)
		return 0;
	else
		return path_cap;
}


void solve()
{
	cout << "Enter the no of nodes and edges in the Network: ";
	cin >> N >> M;

	cout << "Enter the source and destination node: ";
	cin >> S >> D;

	int x, y, wt;
	for(int i = 0; i < M; i++)
	{
		cin >> x >> y >> wt;
		gph[x][y] = wt;		// Edge from x to y with weight = wt
	}

	// Initialising the residual network..Initially same as the original n/w
	memset(rgph, 0, sizeof(rgph));
	for(int i = 0; i < N; i++)
	{
		//cout << "I: " << i << " --> " ;
		for(int j = 0; j < N; j++)
		{
		//	cout << gph[i][j].first << "," << gph[i][j].second << " ";
			rgph[i][j] = gph[i][j];
		}
		//cout << endl;
	}

	int mx_flow = 0;

	while(true)
	{
		int cur_path_capacity = bfs();
		cout << cur_path_capacity << " ";
		if(cur_path_capacity == 0)
			break;
		else
			mx_flow += cur_path_capacity;
	}
	cout << "\n";
	cout << "Max Flow from source to destination in this network is " << mx_flow << "\n";
	return;
}

int main()
{
	solve();
	return 0;
}