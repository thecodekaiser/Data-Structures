// Author: thecodekaiser
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAXN 10005

vector<int> gph[MAXN];
vector<int> VIS(MAXN,0);
vector<int> DIS(MAXN,0);
int MX = 0;

int dis = 0, res;

void bfs(int source)
{
	queue<int> q;
	q.push(source);
	while(!q.empty())
	{
		
		int s = q.front();
		VIS[s] = 1;
		res = s;
//		cout << "From: " << s << " TO: ";
		q.pop();

		for(int i = 0; i < gph[s].size(); i++)
		{
			int w = gph[s][i];	

			if(!VIS[w])
			{
//				cout << w << " ";
				q.push(w);
				DIS[w] = DIS[s] + 1;
				if(DIS[w] > MX)
					MX = DIS[w];	
			}
		}
//		cout << endl;
	}
}

void solve()
{
	int N;
	cin >> N;

	int x, y;
	int start;
	for(int i = 0; i < N-1; i++)
	{
		cin >> x >> y;
		gph[x].push_back(y);
		gph[y].push_back(x);
		start = x;
	}

	bfs(start);
	dis = 0;
	
	for(int i = 0; i < MAXN; i++) VIS[i] = 0, DIS[i] = 0;

//	cout << res << endl;
	bfs(res);
	
	cout << MX <<  endl;
	return;
}

int main()
{
	solve();
	return 0;
}
