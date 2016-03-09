#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 1005

ll BIT[MAXN];

void update(int idx, ll val)
{
	while(idx < MAXN)
	{
		BIT[idx] *= val;
		idx += (idx & -idx);
	}
}

ll get(int idx)
{
	ll res = 1;
	while(idx > 0)
	{
		res *= BIT[idx];
		idx -= (idx & -idx);
	}
	return res;
}

ll range_product(int a, int b)
{
	ll res1 = get(a-1);
	ll res2 = get(b);

	return res2 / res1;
}

void solve()
{

	for(int i = 0; i < MAXN; i++)
	{
		BIT[i] = 1;
	}

	for(int i = 0; i < 10; i++)
		cout << BIT[i] << endl;
	ll N;
	cin >> N;
	ll ptr[N+1];
	for(int i = 1; i <= N; i++) 
	{
		cin >> ptr[i];
		update(i, ptr[i]);
	}
	
	int Q,L,R;
	cin >> Q;
	for(int i = 0; i < Q; i++)
	{
		cin >> L >> R;
		cout << range_product(L,R) << endl;
	}
	return ;
}


int main() {
	// your code goes here
	solve();
	return 0;
}
