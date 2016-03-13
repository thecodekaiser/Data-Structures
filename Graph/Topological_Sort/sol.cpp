// Author: thecodekaiser
/**
 * This one uses a priority queue and gives the lexicographically 
 * least topological sort of a DAG.
 */
// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

#define MXN 10010

struct cmp
{
	bool operator()(int const & A, int const & B)
	{
		return A > B;
	}
};

void solve()
{
	int N, M;
	scanf("%d %d",&N, &M);
	int INDEG[N+1], x, y;
	vector<int> gph[N+1];

	memset(INDEG, 0, sizeof(INDEG));

	priority_queue<int, vector<int>, cmp> pq;

	for(int i = 0; i < M; i++)
	{
		scanf("%d %d",&x, &y);
		INDEG[y]++;
		gph[x].push_back(y);
	}

	for(int i = 1; i <= N; i++)
		if(INDEG[i] == 0)
		{
			pq.push(i);	
		}

	vector<int> ans;
	while(!pq.empty())
	{
		int temp = pq.top();

		pq.pop();

		ans.push_back(temp);
		
		for(int i = 0; i < gph[temp].size(); i++)
		{
			int M = gph[temp][i];
			INDEG[M]--;

			if(INDEG[M] == 0)
				pq.push(M);
		}
	}

	//reverse(ans.begin(), ans.end());
	int flag = 0;
	for(int i = 1; i <= N; i++)
		if(INDEG[i])
		{ flag = 1; break; }

	if(!flag)
	{
		for(int i = 0; i < ans.size(); i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	else
		printf("Cycle exists.\n");
	return;
}

int main()
{
	solve();
	return 0;
}


