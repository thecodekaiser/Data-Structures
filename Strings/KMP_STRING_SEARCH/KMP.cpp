/** 
 * This doc implements KMP.
 * Author: thecodekaiser
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;
int cnt;

// We need the lps array which stores the longest prefix that is also a suffix at position i in the pattern string
void computeLPS(string pat, int M, int * lps)
{
	// M -> Length of pattern
	lps[0] = 0;		// This is always 0
	int i = 1;		// We start from index 1
	int len = 0;		// Length of longest prefix that is also a suffix of a the string ending at i

	while (i < M)
	{
		if(pat[i] == pat[len])
		{				// If there's a match then increase the len
			len++;
			lps[i] = len;
			i++;
		}	
		else
		{	
			// If there is a mismatch after len matches
			if(len != 0)
			{
				len = lps[len-1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
	return;
}


// Function : To search a string in a given text 
void find(string text, string pat)
{
	int N = text.length();		// Length of the text
	int M = pat.length();		// Length of the pattern
	
	int i = 0; 
	int j = 0;
	int * lps = (int *) malloc (M * sizeof(int));
	computeLPS(pat,M,lps);		// Compute the lps array

	for(int k = 0; k < M; k++)
		cout << lps[k] << " ";
	cout << endl;

	while(i < N)
	{
		if(pat[j] == text[i])
		{
			i++;
			j++;
			if(j == M)
			{
				cout << "Found pattern starting at index: " << i - j << endl;
				cnt++;
				j = lps[j-1];
				cout << "Changing j back to: " << j << " and i: " << i << endl;
			}
		}
		else
		{
			// If there is a mismatch after last j characters then 
			if(j != 0)
				j = lps[j-1];
			else
			{
				i++;
			}
		}
	}

	return;
}

void solve()
{
	string pat, text;
	cout << "Enter the search text: " ;
	cin >> text;
	
	cout << "Enter what you want to search: " ;
	cin >> pat;

	find(text,pat);
	cout << "Pattern occurrs " << cnt << " times in the text." << endl;
	cnt = 0;
	return;
}

int main()
{
	solve();
	return 0;
}
	
