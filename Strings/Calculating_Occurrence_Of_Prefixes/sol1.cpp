// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

// This one uses the KMP failure-function
void calcLPS(int * LPS, string str)
{
	LPS[0] = 0;			// This is always 0
	int i = 1;
	int len = 0;
	int N = str.length();

	while(i < N)
	{
		if(str[i] == str[len])
		{
			len++;
			LPS[i] = len;
			i++;
		}
		else
		{
			if(len != 0)
				len = LPS[len-1];
			
			else
				LPS[i++] = 0;
		}
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
	int LPS[N];
	calcLPS(LPS, str);

	cout << "LPS: " ;
	for(int i = 0; i < N; i++)
		cout << LPS[i] << " ";
	cout << endl;


	int ans[N+1];
	memset(ans, 0, sizeof(ans));

	for(int i = 0; i < N; i++)
		ans[LPS[i]]++;		// Increment each one


	for(int i = N; i > 0; i--)
		ans[LPS[i-1]] += ans[i];


	for(int i = 1; i <= N; i++)
		ans[i]++;		// Each prefix comes atleast once


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
