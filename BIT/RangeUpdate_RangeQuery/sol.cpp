// Author: thecodekaiser
// Reference: http://zobayer.blogspot.in/2013/11/various-usage-of-bit.html
//            http://apps.topcoder.com/forums/?module=Thread&threadID=715842&start=0&mc=8 (By Anil Kishore)
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
typedef long long ll;
#define MAXN 100010

class BIT
{
private:
	ll * BIT1;
	ll * BIT2;
	int len;

	// Update in BIT 1
	void SET1(int i, ll val)
	{
		while(i < len)	{ BIT1[i] += val; i = i + (i & -i); }
	}

	// Update in BIT2
	void SET2(int i, ll val)
	{
		while(i < len)	{ BIT2[i] += val; i = i + (i & -i); }
	}

	// Get in BIT 1
	ll GET1(int i)
	{
		ll res = 0;
		while(i >= 1)	{ res += BIT1[i]; i = i - (i & -i); }
		return res;
	}

	// Get in BIT2
	ll GET2(int i)
	{
		ll res = 0;
		while(i >= 1)	{ res += BIT2[i]; i = i - (i & -i); }
		return res;
	}

	// To get sum in range [0,x]
	ll GET(int x)
	{
		return GET1(x)*x - GET2(x);
	}
	

	// Range sum
	ll range_sum(int i, int j)
	{
		return GET(j) - GET(i-1);
	}

public:
	// Constructor
	BIT(int N)
	{
		len = MAXN;
		BIT1 = (ll *) calloc (len, sizeof(ll));
		BIT2 = (ll *) calloc (len, sizeof(ll));
	}

	// Updation: add val to [i,j]
	void update(int i, int j, ll val)
	{
		SET1(i, val), SET1(j+1, -val);

		SET2(i, val*(i-1)), SET2(j+1, -val*j);
	}

	// Sum
	ll sum(int i, int j)
	{
		return range_sum(i,j);
	}

};

void solve()
{
	int N, Q, cmd, p, q;
	ll val;

	scanf("%d %d",&N, &Q);

	BIT bt(N);

	for(int i = 0; i < Q; i++)
	{
		scanf("%d",&cmd);
		if(cmd == 0)
		{
			scanf("%d %d %lld",&p, &q, &val);
		//	cout << p << " " << q << " " << val << endl;
			bt.update(p,q,val);
		}
		else
		{
			scanf("%d %d",&p, &q);
		//	cout << p << " " << q << endl;
			printf("%lld\n",bt.sum(p,q));
		}
	}
	
	return;
}


int main()
{
	int t;
	scanf("%d",&t);	
	while(t--)
		solve();
	return 0;
}
