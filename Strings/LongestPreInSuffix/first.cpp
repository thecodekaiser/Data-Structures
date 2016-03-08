/**
 * Here we are required to find out the string and its length which is the prefix,
 * suffix and also a mid-string (i.e. an infix) of a given string and say none if none exists.
 * Here we use a KMP like failure function and use that to find out the reqd string.
 * Author: thecodekaiser
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;
typedef long long ll;

int pre[1000005];		// Length of longest match from prefix till now

void solve()
{
    string str;			
    cin >> str;				// Input string

    int k = 0;
    str = '$' + str;        		// We add a null sign over therefore we are padding the string 
    int len = str.size();   		// Get the size
    int j = 0;              		// Longest match at any character in the string


    // Start matching from the first character because only then we would find a prefix match
    // E.g. aaaa . Start matching the 2nd position from the longest match till now	

    for (int i = 2; i < len; i++)       
    {
      while (j > 0 && str[j+1] != str[i]) j = pre[j];   // Whenver you find that the prefix match is over then bring it back
      
      if (str[j+1] == str[i]) j++;                      // If next position is a match then move forward
      
      pre[i] = j;                                       // Assign value in pre array        
      if (i < len-1) k = max(k,pre[i]);                 // Length of longest match found so far     
    }

    j = pre[len-1];         // Now we get the longest match at the suffix end

    while (j>0 && j>k) j = pre[j];                     // Keep on going back

    if (j) 
        cout << str.substr(1,j) << endl;		// If you have found a substring that is prefix, suffix and infix then print
    else 
        cout<<"None" << endl;
    return;
}

int main()
{
    solve();
    return 0;
}
