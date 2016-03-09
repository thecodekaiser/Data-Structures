/** 
 * This code uses BIT.
 * Author : thecodekaiser
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;
map<long long, int> mapping;

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
	long long * cPtr;
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
		cPtr = (long long *) calloc (N, sizeof(long long));


		for(int i = 0; i < N; i++)
		{
			cPtr[i] = ptr[i];
		}
	}

	// Function : To delete the BIT
	void del()
	{
		free(bit), free(cPtr);
	}


	
	// Function : To count the no of inversions
	long long countINV()
	{
		long long ans = 0, temp;
		for(int i = len-1; i >= 0; i--)
		{
			long long V = cPtr[i];
			int mp = mapping[V];
			cout << "V: " << V << " mp: " << mp << endl;
			temp = GET(mp-1);
			ans = ans + temp;

			SET(mp,+1);
		}

		return ans;
	}

};


int main()
{
	int N;
	cin >> N;

	long long * men = (long long *) malloc (N * sizeof(long long));
	long long * women = (long long *) malloc (N * sizeof(long long));
	long long * Cwomen = (long long *) malloc (N * sizeof(long long));

	int * ptr = (int *) malloc (N * sizeof(int));

	for(int i = 0; i < N; i++)
	{
		scanf("%lld %lld",&men[i], &women[i]);
		Cwomen[i] = women[i];
	}

	sort(Cwomen, Cwomen+N);
	// Creating an auxiliary array.
	for(int i = 0; i < N; i++)
	{
		long long val = women[i];
		int IND = bs(Cwomen,N,val);
		ptr[i] = IND+1;
	}

	
	for(int i = 0; i < N; i++)
	{
		mapping[men[i]] = ptr[i];
	}

	sort(men, men+N);

	BIT bb(men,N);

	cout << bb.countINV() << endl;

	free(men), free(women), free(ptr), free(Cwomen);
	bb.del();
	mapping.clear();

	return 0;
}
					
