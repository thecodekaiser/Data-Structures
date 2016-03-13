#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
 
#define INF 100010
#define MAXN 100010
 
// Struct
struct edge
{
	int V1, V2, rel;
};
 
// Custom Sort
int comp(edge A, edge B)
{
	if(A.V1 < B.V1)
		return 1;
	else if(A.V1 == B.V1)
	{
		if(A.V2 < B.V2)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
 
// Binary Search
int BS(edge * ptr, int vertex, int lo, int hi)
{
	int mid;
	while(lo < hi)
	{
		mid = lo + (hi-lo)/2;
		if(ptr[mid].V1 == vertex)
			hi = mid;
		else if(ptr[mid].V1 < vertex)
			lo = mid+1;
		else
			hi = mid-1;
	}
 
	return lo;
}
 
// Swap operation
void swap(int * a, int * b)
{
	int t = * a; *a = *b; *b = t;
}
 
// My heap 
int * heap;			// Has vertices
 
// To store ans
int Ver[MAXN][2];		// One column to store min distance and another to store its index in heap
int heap_length;		// Total elements in the heap
				// Leaving 0th index free in this implementation
 
// Sink op	
void sink(int i)
{
	if((2*i > heap_length))	return;
 
	int j = 2 * i;
 
	if(j < heap_length && Ver[heap[j]][0] > Ver[heap[j+1]][0])	j = j+1;		// Among both children find one with smaller value
 	
	if(Ver[heap[j]][0] < Ver[heap[i]][0])
	{
		swap(heap[i],heap[j]);
		Ver[heap[i]][1] = i;				// This effectively stores the index of both 
		Ver[heap[j]][1] = j;
		sink(j);
	}
}
 
// Swim  op
void swim(int i)
{
	if(i == 1)
		return;
 
	int root = i/2;
 
	if(Ver[heap[root]][0] > Ver[heap[i]][0])
	{
		swap(heap[i],heap[root]);
		Ver[heap[i]][1] = i;				// This effectively stores the index of both 
		Ver[heap[root]][1] = root;
		swim(root);
	}
}
 
// Solver Method
void solve()
{
 
	int N, M;
 
	scanf("%d %d",&N, &M);
	edge * ptr = (edge * ) malloc ((2 * M) * sizeof(edge));
	heap = (int *) malloc (MAXN * sizeof(int));
	int X, Y;
 
	for(int i = 0; i < 2*M; i += 2)
	{
		scanf("%d %d",&X, &Y);
//		cout << "X: " <<  X << " Y: " << Y << endl;
 
		ptr[i].V1 = X , ptr[i].V2 = Y, ptr[i].rel = 0;
		ptr[i+1].V1 = Y , ptr[i+1].V2 = X, ptr[i+1].rel = 1;
	}
 
	// Custom sort
	sort(ptr,ptr+(2*M), comp);
 
 
/*	for(int i = 0; i < 2*M; i++)
		cout << "(" << ptr[i].V1 << "," << ptr[i].V2 << "," << ptr[i].rel << ") " ;
	cout << endl;
 */
	// Create the heap and Ver
	for(int i = 1; i <= MAXN; i++)
	{
		heap[i] = i;
		Ver[i][0] = INF;
		Ver[i][1] = i;
	}
 
	heap_length = N;
 
	// Initialise first vertex's shortest distance as 0
	Ver[1][0] = 0;
 
	while(heap_length != 0 && Ver[heap[1]][0] != INF)
	{
		// Selected the top vertex
		int VV = heap[1];
//		cout << "SELECTED " << VV << " IT's current VALUE: " << Ver[VV][0] <<  endl;
 
		// Now get it out of the heap
		swap(heap[1], heap[heap_length--]);
 
		// Change the first's index
		Ver[heap[1]][1] = 1;
 
		// Now sink it down
		sink(1);
 
 
		// Update the neighbours of the selected min vertex
		// Find the index of first occurance of this vertex as V1 in ptr array of edges
		int index = BS(ptr, VV, 0, 2*M-1);
 
		while(ptr[index].V1 == VV)
		{
				// Update all neighbours
				int neigh = ptr[index].V2;
				if(Ver[neigh][0] > Ver[VV][0]+ptr[index].rel)
				{
					Ver[neigh][0] = Ver[VV][0]+ptr[index].rel;
					swim(Ver[neigh][1]);				// Given neighbour's index
				//	cout <<"Neighbour: " << neigh <<  "UPDATED VALUE: " << Ver[neigh][0] << " IT's INDEX " << Ver[neigh][1] << endl;
				}
				index++;
		}
	}
 
	// Now we would have either set a lowest value in the Ver[N][0] or there would be still INF in it
	if(Ver[N][0] == INF)
	{
		printf("-1\n");
	}
	else
		printf("%d\n",Ver[N][0]);
 
	free(heap), free(ptr);
 
	return;
}
 
int main() {
	// your code goes here
	solve();
	return 0;
} 
