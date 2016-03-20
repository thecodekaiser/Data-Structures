/**
 * This question requires us to find the longest common prefix length after some shifts.
 * Here we are using KMP and binary search.
 * The idea is that is that if two strings have a common substring of length n
 * then they also have a common substring of length of size smaller than n. SO 
 * We look at the mid and then if there's a match then we go towards the right part to 
 * determine the length.
 * ELse we go to the left half.SO in all we do  O(lg n) of lookups where n is the length of string.
 * Also during each look up we do O(n) work since it's KMP based . Same would have been the case if 
 * we used Hashing like in Rabin-Karp.
 * I read from various sources to do this. But special thanks to Vinay Guthal(win_ay)
 *
 * Author: thecodekaiser
 */
 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

void computeLPS(string pat, int M, int * lps);
int ans = 0;
long cnt = 0;					// No of matches

// KMP Search
int find(string text, string pat)
{
	int N = text.size();	// Length of text
	int M = pat.size();		// Length of pattern
	
	int * lps = (int *) malloc (M * sizeof(int));
	
	computeLPS(pat,M,lps);			// First compute the lps array / Failure function for the pattern
	int j = 0;						// Index of the pattern
	
	int i = 0;						// Index of text
	
	
	while(i < N)
	{
		if(text[i] == pat[j])
		{
			i++;
			j++;
			
			if(j == M)
			{	
				cnt += 1;
				ans = i-j;
				j = lps[j-1];
				return 1;		// Found the match
			}
		}
		else if(pat[j] != text[i])
		{
			// If mismatch after some matches
			if(j != 0)
			{
				j = lps[j-1];	// Don't match lps[j-1] characters as they will match anyway
			}
			else
				i++;
		}
	}
	free(lps);			// Free Memory to avoid memory leak
	return 0;
}
		
// Function : To compute the failure function 
void computeLPS(string pat, int M, int * lps)
{
	// Initiaise the first position
	lps[0] = 0;				// Can't go back for the first position
	int i = 1, len = 0;		// len -> Length of Longest Prefix Match till now
	
	while(i < M)
	{
		if(pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		
		else
		{
			// A mismatch after j matches
			if(len != 0)
			{
				len = lps[len-1];		// No need to match last lps[len-1] characters
			}
			else  //if(len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

// A -- > Original pat,  B --> Original text
string A, B;

// Function : 
int binary_find(int start, int end)
{
	string pat;			// This I will search in each call
	for(int i = 0; i < end; i++)	// Creating the pattern
		pat.push_back(A[i]);
		
	if(find(pat,B))
	{
		return 0;
	}
	
	if(start + 1 == end)
	{
		// Base case if we have found the max length possible
		
		pat = "";						// Clearing the searched pat
		for(int i = 0; i < start; i++)
			pat.push_back(A[i]);

		if(start != 0)	// To check if no actual substring has been found
			find(pat,B);
		return 0;
	}
	
	int mid = (start + (end-start)/2);
	pat = "";
	for(int i = 0; i < mid; i++)
		pat.push_back(A[i]);		// Creating the pattern
		
	if(find(pat,B))
	{
		return	binary_find(mid,end);		// If middle pattern is there then we can search in the right half
	}
	else
	{
		return binary_find(start,mid);
	}
}
	
int main() {
	
	// your code goes here
	int n;
	scanf("%d\n",&N);
	cin >> A;
	cin >> B;
	B = B + B;
	binary_find(0, B.size());
	
	printf("%d\n",ans);
	return 0;
}
