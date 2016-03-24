/**
 * This code is using BIT to solve the problem HORRIBLE(basically range updates and query)
 *
 * Author: thecodekaiser
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
typedef long long ll;
#define type(x) __typeof((x).begin())

#define MAXN 101010
ll bit[MAXN];
ll arr[MAXN];

void SET(int index, ll val)
{
	while(index < MAXN)
	{
		bit[index] += val;		// Set this value
		index = index + (index & -index);
	}
	return;
}

ll GET(int index)
{
	ll res = 0;
	while(index >= 1)
	{
		res += bit[index];
		index = index - (index & -index);
	}
	return res;
}

// Range update
void update_range(int i, int j, ll val)
{
	SET(i,val);
	SET(j+1, -val);

	return;
}

// Range Query
ll range_query(int i, int j)
{
	ll res;
	res = GET(j) - GET(i-1);
	return res;
}

int read(){int x; scanf("%d",&x); return x;}


void solve()
{
	int N, C, cmd, p, q;
	ll val;
	N = read(), C = read();
	
	memset(arr, 0, sizeof(arr));
	memset(bit, 0, sizeof(bit));

	for(int i = 1; i <= N; i++)
	{
		arr[i] = 0;
		SET(i, arr[i]);
	}

	for(int i = 0; i < C; i++)
	{
		cmd = read();
		if(cmd == 0)
		{
			p = read(), q = read();
			scanf("%lld",&val);
			update_range(p, q, val);
		}
		else
		{
			p = read(), q = read();
			for(int i = p-1; i <= q+1; i++)
				cout << GET(i) << " " ;
			cout << endl;
		}
	}

	return;
}


	
	
int main()
{
	int t = read();
	while(t--)
		solve();
	return 0;
}
