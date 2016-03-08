/**
 * This is an implementation where the construction of Suffix Array 
 * takes O(n *(lg n)^2) time
 * Here we sort the suffixes by their 2^k grams.
 * That is we sort the suffixes first by their first character, then first 2 -> first 4 and so on.
 * Hence it takes just lg N steps and call quicksort which takes O(N * lg N) time
 * So total complexity is O(N * (lg N)^2)
 * I learned it from various sources.
 * Author: thecodekaiser
 * Date : 21st Sep 2014
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>


#define MAXLVL 18
#define MAXLEN 1000005		

using namespace std;


// So now we need something to hold the sort index of a suffix at any stage of the sorting so let's do it
// Let us define a structure to hold that info
struct tuple
{
	int nr[2];
	int original;
}L[MAXLEN];

int sortIndex[MAXLVL][MAXLEN];			// It will hold sort index

// Custom sorting function 
int comp(tuple A, tuple B)
{
	return (A.nr[0] == B.nr[0])? (A.nr[1] < B.nr[1] ? 1 : 0) : (A.nr[0] < B.nr[0] ? 1 : 0);
}

int cnt, step;

// Function : TO give the suffix array for a string
int * giveSuffixArray(string str)
{
	int N = str.size();
	// Now create an array to hold the SortIndex
	
	for(int i = 0; i < MAXLVL; i++)
		for(int j = 0; j < N; j++)
			sortIndex[i][j] =0;
	
	// Now set it for the first character
	for(int i = 0; i < N; i++)
		sortIndex[0][i] = (int)str[i];


	cnt = 1;			// Our loop will run till cnt < N, basically count is the 
	step = 1;				
	for(; cnt < N; step++, cnt *= 2)
	{
		for(int i = 0; i < N; i++)
		{
			L[i].nr[0] = sortIndex[step-1][i];
			L[i].nr[1] = i + cnt < N ? sortIndex[step-1][i+cnt] : -1;		// Set -1 if there is no size left
			L[i].original = i;
		}

		// Now call the sort function 
		sort(L,L+N, comp);
	
		// Update the sort index with the new values
		for(int i = 0; i < N; i++)
		{
			sortIndex[step][L[i].original] = i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1] ? sortIndex[step][L[i-1].original] : i;
		// Check if this value is in the same bucket as the last one
		// If yes then give it this bucket only
		// Else give a new bucket
		}
	}

	// Now we have the suffixes sorted and we can use the info stored in the last step to create the suffix array
	int * SA = (int *) malloc(N * sizeof(int));
	for(int i = 0; i < N; i++)
		SA[i] = L[i].original;
	
	// Now return this result
	return SA;
}

// Function : To find the longest common prefix between two prefixes
int prefix(int x, int y, int N)
{
	int ret = 0, k;
	if(x == y) return N - x;
	for(k = step - 1; k >= 0 && x < N && y < N; k--)
	{
		if (sortIndex[k][x] == sortIndex[k][y])
			x += 1 << k, y += 1 << k, ret += 1 << k;
	}
	return ret;
}

// Function : To compute the lcp array
int * computeLCP(string str, int * SA)
{
	int N = str.size();
	int * lcp = (int *) malloc(N * sizeof(int));
	lcp[0] = 0;
	for(int i = 1; i < N; i++)
	{
		int val = prefix(SA[i-1],SA[i],N);
		lcp[i] = val;
	}
	return lcp;
}

void solve()
{
	string str;
	cin >> str;

	int N = str.length();

	str += str;
	int len = str.length();

	int * SA = giveSuffixArray(str);
	int * LCP = computeLCP(str,SA);	
	
	/*for(int i = 0; i < str.size(); i++)
		cout << SA[i]+1 << " " << str.substr(SA[i]) << endl;

	for(int i = 0; i < step; i++)
	{
		for(int j = 0; j < str.size(); j++)
			cout << sortIndex[i][j] << " " ;
		cout << endl;
	}
	
	for(int i = 0; i < str.size(); i++)
		cout << LCP[i] << " ";
	cout << endl;
	*/
	
	int found = 0;
	int start ;
	int best_start = len + 1;
	for(int i = 0; i < str.size(); i++)
	{
		if(found == 0)
		{
			if(SA[i] + (N-1) <= len-1)
			{
			//	cout << "FOUND at: " << i << " SA[i]: " << SA[i] << endl;
				start = SA[i];
				if(start + 1 > N)	start = start - N + 1;
				if(start < best_start)
					best_start = start;
				found = 1;	
			}
		}
		else
		{
			if(LCP[i] >= N)
			{
			//	cout << "FOUND at: " << i << " SA[i]: " << SA[i] << " LCP[i]: " << LCP[i] << endl;
				if(SA[i] + (N-1) <= len-1)
				{
					start = SA[i];
					if(start + 1 > N)	start = start - N + 1;
					if(start < best_start)
						best_start = start;
					
				}
			}
			else
				break;
		}
	}

	cout << best_start << endl;

	//cout << str.substr(best_start,N) << endl;

/*
	for(int i = 0; i < step; i++)
	{
		for(int j = 0; j < str.size(); j++)
			cout << sortIndex[i][j] << " " ;
		cout << endl;
	}

	for(int i = 0; i < str.size(); i++)
		cout << LCP[i] << " ";
	cout << endl;
*/
	free(SA), free(LCP);
}

int main()
{
	//int t;
	//cin >> t;
	//while(t--)
	solve();
	return 0;
}
