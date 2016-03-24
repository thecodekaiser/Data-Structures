// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;
#define MXN 200010

typedef long long ll;

vector<ll> tree[4*MXN];
ll arr[MXN];

ll in_inv;			// This will store the actual number of inversions before hand

void build(int Node, int l, int r)
{
	if(l == r)
	{
		tree[Node].push_back(arr[l]);
		return;
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

	build(left, l, mid);	build(right, mid+1, r);

	int i = 0, j = 0;
	for(; i < tree[left].size() and j < tree[right].size();)
	{
		if(tree[left][i] > tree[right][j])
		{
			in_inv += (tree[left].size() - i);
			tree[Node].push_back(tree[right][j]);
			j++;
		}
		else if(tree[left][i] <= tree[right][j])
		{
			tree[Node].push_back(tree[left][i]);
			i++;
		}
	//	cout << i << "," << j << endl;
	}

	while(i < tree[left].size())
	{
		tree[Node].push_back(tree[left][i]);
		i++;
	//	cout << "i: " << i << endl;
	}

	while(j < tree[right].size())
	{
		tree[Node].push_back(tree[right][j]);
		j++;
	//	cout << "j: " << j << endl;
	}	
	
	//cout << "L: " << l << " R: " << r << " size: " << tree[Node].size() << endl;
	return;
}

ll prev, next, p;
int a, b;

// It basically finds the no of inversions change in range [i,j]
void find(int Node, int l, int r, int i, int j)
{
	if(l > r or i > r or j < l)
		return;

	if(i <= l and r <= j)
	{
		p++;
		int s = tree[Node].size();

		// Here we find the no of elements that are smaller than arr[a]..they form an inversion
		prev += (lower_bound(tree[Node].begin(), tree[Node].end(), arr[a]) - tree[Node].begin());
		// Here we find how many elements are greater than arr[b]..they also form an inversion
		prev += (tree[Node].begin() + s - upper_bound(tree[Node].begin(), tree[Node].end(), arr[b]));

		// Now we calculate the ans for next
		next += (lower_bound(tree[Node].begin(), tree[Node].end(), arr[b]) - tree[Node].begin());
		next += (tree[Node].begin() + s - upper_bound(tree[Node].begin(), tree[Node].end(), arr[a]));
		
		return;
	}

	int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	
	find(left, l, mid, i, j);
	find(right, mid+1, r, i, j);
}

void swap(int & a, int & b)
{    int temp = a; a = b; b = temp;	}

void solve()
{
	int N, M;
	cin >> N >> M;

	for(int i = 0; i < N; i++)
		cin >> arr[i];

	build(1, 0, N-1);

	//cout << "BUILT" << endl;

	while(M--)
	{
		cin >> a >> b;

		a--, b--;
		if(b < a) swap(a,b);

		prev = 0, next = 0, p = 0;

		// Calculate for range [a+1, b-1]

		find(1, 0, N-1, a+1, b-1);

	//	cout << prev << " " << next << endl;
		if(arr[a] > arr[b])	  prev++;			// Earlier (a,b) constituted an inversion
		else if(arr[a] < arr[b])  next++;		// Now (a,b) constitute an inversion

	//	cout << prev << " " << next << endl;
		ll adj = next-prev;					// This is the change in the inversions that can happen

		printf("%lld\n",in_inv+adj);
	}
	return;
}

int main()
{
	solve();
	return 0;
}


