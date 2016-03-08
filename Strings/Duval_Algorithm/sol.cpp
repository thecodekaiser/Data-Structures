// Author: thecodekaiser
/*
 * This is an implementation of the Duval algorithm to find the minimum lexicographical 
 * rotation of a given string. 
 */
#include <bits/stdc++.h>
using namespace std;

void solve()
{
	string s; 
	cin >> s;
	s = s + s;

	int n = (int) s.length();
	int i=0, ans;
	while (i < n/2)
	{
		ans = i;
		int j = i+1, k = i;
		while(j  < n and s[k] <= s[j])
		{
			if(s[k] < s[j])
				k = i;
			else
				k++;
			j++;
		}

		while(i <= k) i += (j-k);
	}

	cout << ans << endl;
	//cout << s.substr(ans,n/2) << endl;
	
	return;
}

int main()
{
	solve();
	return 0;
}