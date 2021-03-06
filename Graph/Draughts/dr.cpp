#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>
 
using namespace std;
#define pb push_back
#define MAXN 50005

long long int R;
bool visited[MAXN];
int room[MAXN];
vector<int> graph[MAXN];

long long dfs(int V)
{
	if(!visited[V])
	{
		visited[V] = 1;
		long long ans = 0;
		if(room[V] == 1)
			ans = 1;
	
		for(int i = 0; i < graph[V].size(); i++)
		{
			if(!visited[graph[V][i]])
			{
				ans += dfs(graph[V][i]);
			}
		}
		
		if(ans > 0)
			R++;
		
		return ans;
	}
}

void solve()
{
	int N, M;
	scanf("%d %d",&N, &M);
		
	for(int i = 1; i <= N; i++)
	{
		scanf("%d",&room[i]);
		visited[i] = false;
	}

	int x, y;
	for(int i = 1; i <= M; i++)
	{
		scanf("%d %d",&x, &y);
		graph[x].pb(y);
		graph[y].pb(x);
	}

	long long ans = 0;
	long long s;
	for(int i = 1; i <= N; i++)
	{
		if(!visited[i] and room[i] == 1)
		{
			s = dfs(i);
			ans = ans + ((s*(s-1))/2);

			if(s == 1)
				R--;
		}
	}

	printf("%lld %lld\n",ans,R);
	return;
}
 
int main()
{
	solve();
	return 0;
} 
