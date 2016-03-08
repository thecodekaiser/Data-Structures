// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<string> permute(string str)
{
	if(str.length() == 1)
	{
		vector<string> ret; ret.push_back(str);
		return ret;
	}
	else
	{
		vector<string> ret;

		for(int i = 0; i < str.length(); i++)
		{
			char ch = str[i];
			string aux = str.substr(0, i) + str.substr(i+1);
			vector<string> auxSet = permute(aux);

			for(int j = 0; j < auxSet.size(); j++)
			{
				aux = ch + auxSet[j];
				ret.push_back(aux);
			}
		}

		return ret;
	}
}

void solve()
{
	string str;
	cin >> str;

	sort(str.begin(), str.end());

	cout << str << endl;

	vector<string> stSet = permute(str);

	for(int i = 0; i < stSet.size(); i++)
		cout << stSet[i] << endl;

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