/**
 * This code is using BIT to solve the problem of finding the length of the 
 * longest decreasing subsequence in O(N lg N) time.
 *
 * Now a thing to note: Length of longest increasing subsequence = Min no of increasing subsequences to cover the whole sequence 
 * Additional info is given in the code.
 * Author: thecodekaiser
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define type(x) __typeof((x).begin())

template <class T> inline void uMax(T & a,T b){if(a < b) a = b ; }	// Compares a and b and changes a to max of both
template <class T> inline void uMin(T & a,T b){if(a > b) a = b ; }	// Compares a and b and changes a to min of both
template <class T> inline T abs(T a){return a>0 ? a : -a;}		// Gives the absolute value
template <class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}		// Gives the lcm of two values

#define N 101010
int bit[N];
int arr[N];

void SET(int index, int val)
{
	while(index < N)
	{
		uMax(bit[index],val);		// Set this value
		index = index + (index & -index);
	}
	return;
}

int GET(int index)
{
	int res = 0;
	while(index > 0)
	{
		uMax(res,bit[index]);
		index = index - (index & -index);
	}
	return res;
}

int read(){int x; scanf("%d",&x); return x;}

// This code gives the length of the longest increasing subsequence
int main()
{
	int n = read();

	for(int i = 1; i <= n; i++)
	{	
		arr[i] = read();
	}

	// This reversal gives us the longest decreasing subsequence
	reverse(arr+1, arr+1+n);
	
	for(int i = 1; i <= n; i++)
	{
		SET(arr[i], GET(arr[i]-1) + 1);
	}
	
	cout << GET(N-1) << endl;
	return 0;
}
