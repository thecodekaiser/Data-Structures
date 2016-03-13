/**
 * Author: thecodekaiser
 * This one solves the LCA problem in <N lg N, lg N> time 
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 1010
int timer, l;

vector<int> gph[MXN];
vector<int> up[MXN];
vector<int> in(MXN), out(MXN);

void dfs (int v, int p = 1) 
{
	in[v] = ++ timer;
	up[v][0] = p;
	
	for (int i = 1; i <= l; ++ i)
		up[v][i] = up[up[v][i-1]][i-1];
	
	for (size_t i = 0; i < gph[v].size(); ++i)
	{
		int to = gph[v][i];
		if (to != p)
			dfs (to, v);
	}
	out [v] = ++timer;
}

bool upper (int a, int b) 
{
	return in [a] <= in [b] && out [a] >= out [b];
}

int lca (int a, int b) 
{
	if (upper (a, b)) return a;
	if (upper (b, a)) return b;

	for (int i = l; i >= 0; --i)
		if (! upper (up [a] [i], b))
			a = up [a] [i];

	return up [a] [0];
}
	
void solve(int CS)
{
	int N;
	scanf("%d",&N);

	timer = 0;
	for(int i = 1; i <= N; i++)
	{
		gph[i].clear();
	}

	in.resize(N+1), out.resize(N+1);	
	
	l = 1;
	while((1 << l) <= (N+1)) l++;

	for(int i = 1; i <= N; i++)
		up[i].resize(l+1);

	int M, val;

	for(int i = 1; i <= N; i++)
	{
		scanf("%d",&M);

		for(int j = 0; j < M; j++)	
		{
			scanf("%d",&val);
			gph[i].push_back(val);
		}
	}		

/*	
	for(int i = 1; i <= N; i++)
	{
		cout << i << " --> " ;
		for(int j = 0; j < gph[i].size(); j++)
			cout << gph[i][j] << " ";
		cout << endl;
	}
*/

	//cout << "Here" << endl;

	dfs(1);		// Void dfs

	//cout << "HERE" << endl;
	
	int Q, x, y;
	scanf("%d",&Q);
	printf("Case %d:\n", CS);
	while(Q--)
	{
		scanf("%d %d",&x, &y);
		printf("%d\n", lca(x,y));
	}

	return;
}

int main()
{
	int t, CS = 1;
	cin >> t;
	while(t--)
		solve(CS++);

	return 0;
}
