#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

// This function sorts an array of strings using Key-Indexed counting in LSD fashion
void LSDsort(string arr[], int N)
{
	// W -> The length of each of the ptr[i] element
	// N -> Length of the ptr array	
	int R = 256;			// Extended ASCII size
	int W = arr[0].length();	// Size of each string

	// Now allocate size for an auxiliary array
	string * aux = new string[N];

	// Initialize the aux array
	for(int i = 0; i < N; i++)
		aux[i] = arr[i];

/*	cout << "Initialisations done" << endl;

	cout << "BEFORE: AUX: " << endl;
	for(int i = 0; i < N; i++)
		cout << aux[i] << endl;
*/
	// Create the count array
	int * cnt = (int *) calloc (R+1, sizeof(int));

	// Start from the least significant digit first
	for(int d = W-1; d >= 0; d--)
	{
		memset(cnt, 0, sizeof(int)*(R+1));

		// Now traverse the d th digits
		for(int i = 0; i < N; i++)
			cnt[arr[i][d] + 1]++;		// Increase by one

		// Now accumulate the indices
		for(int r = 0; r < R; r++)
			cnt[r+1] += cnt[r];

		// Now move data
		for(int i = 0; i < N; i++)
			aux[cnt[arr[i][d]]++] = arr[i];

		// Copy back into original
		for(int i = 0; i < N; i++)
			arr[i] = aux[i];
	}

	// Free unused memory
	free(cnt);
	delete [] aux;

}

void do_it()
{
	int N;
	int W = 31;
	scanf("%d",&N);
	string arr[N];

	string str;

	map<string, int>  MP;

	getchar();
	for(int i = 0; i < N; i++)
	{
		getline(cin,arr[i]);
		//if(i == N-1)
		//	arr[i] = arr[i] + " ";

		if(MP.count(arr[i]) == 0)
			MP.insert(pair<string,int>(arr[i],1));
		else
			MP[arr[i]] += 1;
		
	}

/*	cout << "THE ARRAY LOOKS LIKE: " << endl;
	for(int i = 0; i < N; i++)
		cout << arr[i] << endl;

*/
//	cout << "GOING" << endl;
	LSDsort(arr, N);
//	cout << endl;
	for(int i = 0; i < N; i++)
	{
		int cnt = MP.at(arr[i]);
		if(cnt == 1)
			cout << arr[i] << " " << cnt << endl;
		else
		{
			cout << arr[i] << " " << cnt << endl;
			i += (cnt) - 1;
		}	
	}	
	cout << endl;		

}

int main()
{
	int t;
	scanf("%d",&t);
	getchar();
	while(t--)
	{
		do_it();
		getchar();
	}

	return 0;
}
