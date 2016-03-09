/**
 * This code implements a BIT to count the no of inversions in an array. 
 * At each point we need to ans one thing..how many no in the array
 * are smaller than the given element.
 * 
 * More explaination to follow in the code.
 * Author: thecodekaiser
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

// Function : Binary Search
int bs(long long * ptr, int N, long long val)
{
	int lo = 0, hi = N-1;
	int mid;
	while(lo <= hi)
	{
		mid = lo + ((hi-lo) >> 1);
		if(ptr[mid] == val)
			return mid;
		else if(ptr[mid] < val)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return -1;
}


// Defining the BIT class
class BIT
{

// Private Global variables
private:
	long * bit;
	long * cPtr;
	int len;

	// Function : To set a value at a particular index
	void SET(int V, int val)
	{
		while(V <= len)
		{
			bit[V] += val;
			V = V + (V & (-V));
		}
		return ;
	}

	// Function : To get a value at a particular index

	long GET(int V)
	{
		long ans = 0;
		while (V > 0)
		{
			ans += bit[V];
			V = V - (V & (-V));
		}
		return ans;
	}


public: 
	// Constructor
	BIT(long long * ptr, int N)
	{
		len  = N;					// Length of the cPtr
		bit  = (long *) calloc (N+1, sizeof(long));
		cPtr = (long *) calloc (N, sizeof(long));

		long long * copy = (long long *) calloc (N, sizeof(long long));
		for(int i = 0; i < N; i++)
		{
			copy[i] = ptr[i];
		}
		sort(copy, copy+N);
		for(int i = 0; i < N; i++)
		{
			long long v = ptr[i];
			int in = bs(copy,N,v);
			cPtr[i] = in+1;
		}

		/*for(int i = 0; i < N; i++)
			cout << cPtr[i] << " " ;
		cout << endl;
		*/
		
		free(copy);
	}


	
	// Function : To count the no of inversions
	long long countINV()
	{
		long long ans = 0, temp;
		for(int i = len-1; i >= 0; i--)
		{
			int V = cPtr[i]; 
			temp = GET(V-1);
			ans = ans + temp;

			SET(V,+1);
		}

		return ans;
	}

};

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int N;
		scanf("%d",&N);
		long long * ptr = (long long *) malloc (N * sizeof(long long));
		for(int i = 0; i < N; i++)
			scanf("%lld",&ptr[i]);

		BIT bb(ptr,N);

		printf("%lld\n",bb.countINV());
	}
	return 0;
}
					
