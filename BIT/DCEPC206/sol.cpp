#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

#define MAXN 1000005

ll BIT[MAXN];

void set(int i, ll val)
{
	int in = i;
	while(in < MAXN)
	{
		BIT[in] += val;
		in = in + (in & -in);
	}
	return;
}

ll get(int i)
{
	ll res = 0;
	int in = i;
	while(in >= 1)
	{
		res += BIT[in];
		in = in - (in & -in);
	}
	return res;
}

void solve()
{
	int N;
	scanf("%d",&N);
	
	memset(BIT, 0, sizeof(BIT));
	ll ans = 0;
	ll v;
	for(int i = 0; i < N; i++)
	{
		scanf("%lld",&v);
		if(v != 0)
		{
			ans += get(v-1);
			set(v,v);
		}
	}
	
	printf("%lld\n",ans);
	return;
}


int main() {
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}