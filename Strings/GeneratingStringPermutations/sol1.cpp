// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int str_len;

void recur(string cur, vector<int> cnt, int curLen)
{
	if(curLen == str_len)
	{
		cout << cur << endl;
		return;
	}
	else
	{
		for(int i = 0; i < 26; i++)
		{
			if(cnt[i])
			{	
				cnt[i]--;
				char aux = (char)(i + 'a') ;
				recur(cur + aux, cnt, curLen+1);
				cnt[i]++;
			}
		}
		return;
	}
}

void solve()
{
	string str;
	cin >> str;

	vector<int> cnt(26, 0);

	for(int i = 0; i < str.length(); i++)
		cnt[str[i] - 'a']++;

	str_len = str.length();
	string aux = "";
	int len = 0;

	recur(aux, cnt, len);
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