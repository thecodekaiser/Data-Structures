// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

// Gonna solve this problem using the Z-Algorithm
void computeZ(int * Z, string str)
{
	Z[0] = 0;		// First value is always 0
	int L = 0, R = 0;

	int N = str.length();

	for(int i = 1; i < N; i++)
	{
		if(i > R)
		{
			// No Z-Box has reached its end point till i
			// So we can do a fresh scan comparing str[0..] with str[i...]
	
			L = R = i;
			while(R < N and str[R-L] == str[R]) R++;
			Z[i] = R-L;	// Length of prefix
			R--;
		}
		else
		{
			// This is the case where i lies in the computed Z-Box

			int K = i - L;			// This is where we will find K in the prefix
			
			if(Z[K] < R - i + 1)
				Z[i] = Z[K];		// Now we can't extend it
			else
			{
				L = i;			// Now we got to compute new Z-Box
				while(R < N and str[R-L] == str[R]) R++;
				Z[i] = R - L;
				R--;
			}
		}
	}

	return;
}

void solve()
{
	string str;
	cin >> str;

	int maxz, res;
		
	maxz = res = 0;

	int N = str.size();	

	int Z[N];
	computeZ(Z, str);

	for(int i = 0; i < N; i++)
	{
	//	cout << Z[i] << " ";
		if(Z[i] == N-i and maxz >= N-i)
		{	res = N-i; break;	}

		maxz = max(maxz, Z[i]);
	}
	//cout << endl;

	if(!res)
		cout << "Just a legend\n";
	else
		cout << str.substr(0, res) << "\n";
	return;
}

int main()
{
	solve();
	return 0;
}
