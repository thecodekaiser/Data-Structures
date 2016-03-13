// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 105
int gph[MXN][MXN];	// Adjacency list
int dis[MXN][MXN];	// Shortest Distance of node i to node j

void solve()
{
	memset(gph, 0, sizeof(gph));
	memset(dis, 0, sizeof(dis));
	int N, M, x, y, w;

	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		cin >> x >> y >> w;
		gph[x][y] = gph[y][x] = 1;
		dis[x][y] = dis[y][x] = w;
	}

	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if(i != j and gph[i][k] and gph[k][j])
					if(dis[i][j] > (dis[i][k] + dis[k][j]))
						dis[i][j] = dis[i][k] + dis[k][j];
	
	
	return;
}

int main()
{
	solve();

	return 0;
}
