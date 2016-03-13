#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
typedef long long ll;
#define MAXN 10005
 
vector<ll> vertex[MAXN];
int VISITED[MAXN];
 
// Function : TO initialise
void init()
{
	for(int i = 0; i < MAXN; i++)
	{
		vertex[i].clear();
	}
}
 
int RES;

// DFS
void dfs(int index)
{
	if(!VISITED[index])
	{
		int N = vertex[index].size();
		VISITED[index] = 1;

		for(int i = 0; i < N; i++)
		{
			int w = vertex[index][i];
			if(VISITED[w] == 1)
			{
				RES = 1;
				return;
			}
			else if(VISITED[w] == 0)
			{
			//	cout << "DFS ON: " << w << endl;
				dfs(w);
			}
		}
	}
}
 
 
// Solver
void solve()
{
	init();
	int N, M;
	cin >> N >> M;

	//cout << N << " " << M << endl;

	ll x, y;
	for(int i = 0; i < M; i++)
	{
		cin >> x >> y;
		vertex[x].push_back(y);
	}

/*
	for(int i = 1; i <= N; i++)
	{
		cout << i << " --> " ;
		for(int j = 0; j < vertex[i].size(); j++)
		{
			cout << vertex[i][j] << " ";
		}
		cout << endl;
	}
*/	
	dfs(1);

	int flag = 0;
	for(int i = 1; i <= N; i++)
		if(VISITED[i] == 0)
		{	flag = 1; break;	}

	if(RES || flag == 1)
		cout << "NO" << endl;
	else if(RES == 0 && flag == 0)
		cout << "YES" << endl;
	

	return;
}
 
int main()
{
	solve();
	return 0;
} 
