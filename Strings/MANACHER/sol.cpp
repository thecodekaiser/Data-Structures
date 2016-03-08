// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 6005

int p[MXN];			// p[i] = length of longest palindromic substring of t centered at i
string str;			// Original string
char t[MXN];		// Transformed string

// Transforms s into t
// For example if s = 'abba', then t = "$#a#b#b#a#@"
void preprocess()
{
	memset(p, 0, sizeof(p));
	memset(t, 0, sizeof(t));
	
	int N = str.length();
	t[0] = '$';
	t[2*N+2] = '@'; 
	for(int i = 0; i < N; i++)
	{
		t[2*i+1] = '#';
		t[2*i+2] = str[i];
	}
	
	t[2*N+1] = '#';
	
	return;
}

void solve()
{
	cin >> str;
	preprocess();

	int center = 0, right = 0;
	int N = strlen(t);
	
	cout << t << endl;
	
	for(int i = 1; i < N-1; i++)
	{
		int mirror = 2 * center - i;		// Equals C - (i - C)
		if(i < right)	p[i] = min(right-i, p[mirror]);
		
		// Try to expand the palindrome centered at i
		while(t[i + (1 + p[i])] == t[i - (1 + p[i])])
			p[i]++;
			
		// If need to change the center and right then change
		if(i + p[i] > right)
		{
			center = i;
			right = i + p[i];
		}
	}
	

	// Find the max len in p
	int mx = 0, cen = 0, cnt = 0;
	for(int i = 1; i < N-1; i++)
	{
//		cout << p[i] << " ";
		if(p[i] > mx)
		{
			mx = p[i];
			cen = i;
			cnt = 1;
		}
		else if(p[i] == mx) cnt++;
	}
//	cout << endl;
	
	cout << str.substr((cen - 1 - mx)/2, mx) << endl;
	cout << mx << " " << cnt << endl;
	
	
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
