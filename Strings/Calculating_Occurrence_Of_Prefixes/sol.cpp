// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

// This one uses the Z-Algorithm
void computeZ(int * Z, string str)
{
	Z[0] = 0;
	int L = 0, R = 0;
	int i = 1;

	int N = str.size();

	while(i < N)
	{
		if(i > R)
		{
			L = R = i;
			while(R < N and str[R-L] == str[R]) R++;

			Z[i] = R-L; R--;
		}
		else
		{
			int K = i - L;
			if(Z[K] < R - i + 1) Z[i] = Z[K];
			else
			{
				L = i;
				while(R < N and str[R-L] == str[R]) R++;
				
				Z[i] = R-L; R--;
			}
		}
		
		i++;
	}

	return;
}

/*
 * Problem : To compute the no of occurrences of each prefix in the whole string.
 */
void solve()
{
	string str;
	cout << "Enter the string: " ;
	cin >> str;

	int N = str.length();
	int Z[N];
	computeZ(Z, str);

//	cout << "COMPUTED" << endl;

	int ans[N+1];
	memset(ans, 0, sizeof(ans));

	for(int i = 0; i < N; i++)
		ans[Z[i]]++;		// Increment each one

//	cout << "1" << endl;

	for(int i = N-1; i > 0; i--)
		ans[i] += ans[i+1];

//	cout << "2" << endl;

	for(int i = 1; i <= N; i++)
		ans[i]++;		// Each prefix comes atleast once

//	cout << "3" << endl;

	for(int i = 1; i <= N; i++)
	{
		cout << "Prefix: " << str.substr(0, i) << " Count: " << ans[i] << endl;
	}

	return;
	
}

int main()
{
	int t;
	cin >> t;
	while(t--)
		solve();
	return 0;
}
