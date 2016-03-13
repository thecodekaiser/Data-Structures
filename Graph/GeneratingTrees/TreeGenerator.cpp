// Author: thecodekaiser
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <ctime>
 
using namespace std;
#define REP(i,N)	for(int i = 0; i < N; i++)
typedef long long ll;
 
class WeightedQU
{
public:
	int * id, * sz;
	int count;

	// Public constructor
	WeightedQU(int N)
	{
		count = N;
		id = (int *) calloc (N+1,sizeof(int));
		sz = (int *) calloc (N+1,sizeof(int));
		for(int i = 0; i < N+1; i++)
		{
			id[i] = i;
			sz[i] = 1;
		}
	}


	// Function: To return the number of components
	int CNT()
	{ 
		return count;
	}

	// Function: To give the root of a node in the tree
	// Uses path compression
	// What we are doing is that we are pointing all members of a component directly to the root
	int find(int p)
	{
		int root = p ;
		while (root != id[root])
			root = id[root];
		while (p != root)
		{
			int newp = id[p];
			id[p] = root;           // Here we are directly pointing every element to the root directly which will help us later
			p = newp;
		}
		return root;
	}

	// Function: To check if two components are connected i.e are in the same component
	int connected(int i, int j)
	{
		return find(i) == find(j);
	}

	// Function : To connect two elements using the weighting principle
	void join(int i, int j)
	{
		int p = find(i);
		int q = find(j);
		if (p == q) return ;

		// Point smaller tree to the larger tree
		if	(sz[p] < sz[q])	{ id[p] = q;	sz[q] += sz[p]; }
		else			{ id[q] = p;	sz[p] += sz[q]; }
		count --;
		return ;
	}

	// This function creates a tree
	void createTree(int N)
	{

		string file_name;
		cout << "Enter the file name: ";
		cin >> file_name;
	
		ofstream file_writer(file_name.c_str());
		if(!file_writer.is_open())
			cout << "Couldn't open the file" << "\n";


		int CNT = 0;
		file_writer << N << "\n";
		while(CNT != N-1)
		{
			int X = rand() % (N) + 1;
			int Y = rand() % (N) + 1;
			if(X == Y) 
				continue;
	
			else if(X != Y and !connected(X,Y))
			{
				//cout << X << " " << Y << "\n";
				file_writer << X << " " << Y << "\n";
				join(X,Y);
				CNT++;
			}
		}
	}	
};

int main()
{
	int T, N;
	cout << "Enter the no of test cases: " ;
	cin >> T;
	srand(time(NULL));
	while(T--)
	{
		cout << "New Case" << endl;
		cout << "Enter the no of nodes: " ;
		cin >> N;
		WeightedQU wq(N);
		wq.createTree(N);
		cout << "Done" << endl;
	}

	return 0;
}
	
