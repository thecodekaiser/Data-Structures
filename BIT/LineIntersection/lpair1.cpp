// Here we can use the merge sort sub-procedure merge to count the
// no of inversions in N lg N time
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

#define x getchar()
#define y putchar
map<ll,ll> mapping;

//Fast input
void read( ll &n )
{
	n = 0;
	int ch = x,sign = 1;
	while( ch < '0' || ch > '9' ){if(ch == '-') sign = -1; ch = x;}
	while( ch >= '0' && ch <= '9' )
 		n= n * 10 + ch - '0', ch=x;
	n = n * sign;
}

//Fast output
void out(ll k)
{
	ll n = k,i = 0;
	char ch[15];
	if(n <= 0) {
		if (n == 0) y('0');		
		else 	y('-');
		n = n * (-1);
	}
	while(n > 0) {
		ch[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	while(i > 0) {
		y(ch[i-1]);
		i--;
		}
	y('\n');
}

// Merge subroutine
inline ll merge(ll * a, ll * aux, int lo, int mid, int hi)
{
	ll inversions = 0;
	// Copy to aux
	for(int k = lo; k <= hi; k++)
		aux[k] = a[k];

	// Merge back to a[]
	int i = lo, j = mid+1;
	for(int k = lo; k <= hi; k += 1)
	{
		if(i > mid)				      a[k] = aux[j++];
		else if(j > hi)				      a[k] = aux[i++];
		else if(mapping[aux[j]] < mapping[aux[i]])   {a[k] = aux[j++]; inversions += (mid - i + 1);}
		else					      a[k] = aux[i++];		// TO keep the sort stable
	}
	return inversions;
}

// Returns the no of inversions in the subarray b
// Also rearranges the sub-array in ascending order
ll count(ll * a, ll * b, ll * aux, int lo, int hi)
{
	ll inversions = 0;
	if(hi <= lo) return 0;
	int mid = lo + (hi-lo)/2;
	inversions	+=	(count(a,b,aux,lo,mid));
	inversions	+=	(count(a,b,aux,mid+1,hi));
	inversions	+=	 merge(b,aux,lo,mid,hi);
	return inversions;
}

// Function that we call
ll cnt(ll * a,ll size)
{
	ll n = size;
	ll * b = (ll *)calloc(n,sizeof(ll));
	ll * aux = (ll *)calloc(n,sizeof(ll));
	
	// Copy a[] to b[]
	for(ll i = 0; i < n; i++)	b[i] = a[i];
	
	ll inv = count(a,b,aux,0,n-1);
	free(b);
	free(aux);
	return inv;
}

int main()
{
	ll n;
	read(n);
	ll * ptr =(ll *)calloc(n,sizeof(ll));
	ll val;
	for(ll i = 0; i < n; i++)
	{
		read(ptr[i]), read(val);
		mapping[ptr[i]] = val;
	}
	
	sort(ptr, ptr+n);

	ll inv = cnt(ptr,n);
	printf("%lld\n",inv);
	free(ptr);
	return 0;
}
