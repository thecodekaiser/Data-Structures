// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 3050

struct edge
{
	int src, dest, len;

	edge() {}
	edge(int s, int d, int l) { src = s, dest = d, len = l; }
};

vector< edge > gph[MXN];
bool flag[MXN];

class comp
{
public:
	bool operator()(const edge & A, const edge & B)
	{
		return A.len > B.len;
	}
};

void solve()
{
    int N, M, st, x, y, r;
    scanf("%d %d", &N, &M);
    
    for(int i = 1; i <= N; i++)
    {
        gph[i].clear();
        flag[i] = false;
    }
    
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d %d", &x, &y, &r);
        gph[x].push_back(edge(x, y, r));
        gph[y].push_back(edge(y, x, r));
    }

    scanf("%d", &st);
    
	// Now applying the Prim's algo
	priority_queue < edge, vector<edge>, comp > pq;

	pq.push(edge(1, 1, 0));

	ll sumMST = 0;
	int numEdges = 0;
	memset(flag, 0, sizeof(flag));

	while(!pq.empty())
	{
		edge temp = pq.top();	
		pq.pop();

		if(flag[temp.dest])	continue;

		//cout << temp.src << "," << temp.dest << "," << temp.len << endl;

		flag[temp.dest] = true;

		numEdges++;
		sumMST += (temp.len);

		for(int i = 0; i < gph[temp.dest].size(); i++)
		{
			edge child = gph[temp.dest][i];

			pq.push(child);
		}
	}

    cout << sumMST << endl;
	return;
}

int main()
{
	solve();
	return 0;
}
