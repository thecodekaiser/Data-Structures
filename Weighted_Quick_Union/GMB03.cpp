/* Here I am implementing the weighted_quick union data-structure.
   This data-srructure allows us to quickly find if we have two connected
   components in the data.
*/


#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
 
using namespace std;
#define REP(i,N)	for(int i = 0; i < N; i++)
 
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
		sz = (int *) calloc (N+1,sizeof(int));
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
		else				        { id[q] = p;	sz[p] += sz[q]; }
		count --;
		return ;
	}
}; 
void solve()
{
	int C, B, Q, x, y;
	scanf("%d %d %d",&C, &B, &Q);
	WeightedQU qf(C);
 
	REP(i,B)
	{
		scanf("%d %d",&x,&y);
		qf.join(x,y);
	}
 
	REP(i,Q)
	{
		scanf("%d %d",&x,&y);
		if(qf.connected(x,y))
			printf("only bus\n");
		else
			printf("bus and taxi\n");
	}
}
 
int main()
{
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--)
	{
		solve();
	}
	return 0;
} 
