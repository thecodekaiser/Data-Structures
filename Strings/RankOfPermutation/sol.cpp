// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll getRank(string str)
{
	ll rank = 1;
	ll suffixPerm = 1;
	map<char, int> mp;

	for(int i = str.length()-1; i > -1; i--)
	{
		char ch = str[i];
		mp[ch]++;

		for(auto it = mp.begin(); it != mp.find(ch); it++)
			rank += suffixPerm * it->second / mp[ch];

		suffixPerm *= (str.length() - i);
		suffixPerm /= mp[ch];
	}

	return rank;
}

void solve()
{
	string str;
	cin >> str;

	cout << getRank(str) << endl;
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