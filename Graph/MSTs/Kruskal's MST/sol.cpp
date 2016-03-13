// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class WeightedQU
{
public:
	int * id, * sz;
	int count;

	// Public constructor
	WeightedQU(int N)
	{
		count = N;
		id = (int *) calloc (N+1,sizeof(int));
        sz = (int *) calloc (N+1, sizeof(int));
		for(int i = 0; i < N+1; i++)
		{
			id[i] = i;
            sz[i] = 1;
		}
	}


	// Function: To return the number of components
	int CNT()
	{ 
		return count;
	}

	// Function: To give the root of a node in the tree
	// Uses path compression
	// What we are doing is that we are pointing all members of a component directly to the root
	int find(int p)
	{
		int root = p ;
		while (root != id[root])
			root = id[root];
		while (p != root)
		{
			int newp = id[p];
			id[p] = root;           // Here we are directly pointing every element to the root directly which will help us later
			p = newp;
		}
		return root;
	}
	
	// Function: To check if two components are connected i.e are in the same component
	int connected(int i, int j)
	{
		return find(i) == find(j);
	}
	
	// Function : To connect two elements using the weighting principle
	void join(int i, int j)
	{
		int p = find(i);
		int q = find(j);
		
		if (p == q) return ;
		
		// Point smaller tree to the larger tree
		if	(sz[p] < sz[q])			{ id[p] = q;	sz[q] += sz[p]; }
		else                        { id[q] = p;	sz[p] += sz[q]; }
		
		count --;
		
		return ;
	}
};

void solve()
{
    int N, M,st, x, y, d;
    cin >> N >> M;
    
    WeightedQU wq(N);
    
    vector< pair<int, pair<int,int> > > vct(M);
    
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d %d",&vct[i].second.first, &vct[i].second.second, &vct[i].first);
    }
    
    scanf("%d", &st);
    
    sort(vct.begin(), vct.end());
   // cout << "HERE" << endl;
    
    int sum = 0;
    
    for(int i = 0; i < M and wq.CNT() > 1; i++)
    {
       // cout << "cnt: " << wq.CNT() << " i: " << i << endl;
        
        int x = vct[i].second.first;
        int y = vct[i].second.second;
       // cout << "x: " << x << " y: " << y << endl;
        
        if(!wq.connected(x, y))
        {
            wq.join(x, y);
            sum += vct[i].first;
        }
    }
    
    cout << sum << endl;
    
    return;
}

int main()
{
    solve();
    return 0;
}