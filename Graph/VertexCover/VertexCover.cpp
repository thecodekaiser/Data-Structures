
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
 
using namespace std;
typedef long long ll;
#define MAXN 100005

// Does DFS on the tree
void dfsTree(vector< vector<int> > & Graph, vector<bool> & visited, vector<bool> & matched, vector<int> & minCover, int current)
{
 	visited[current] = true;


	for(int i = 0; i < Graph[current].size(); i++)
	{
		int childNode = Graph[current][i];
		if( !visited[childNode] )
		{
			dfsTree(Graph, visited, matched, minCover, childNode);


			if(!matched[childNode] && !matched[current])
			{
				//add edge to matching by adding 
				//both of its adjacent vertices
				//cout << "Current: " << current << " ChildNode: " << childNode << endl;
				matched[current] = true;
				matched[childNode] = true;


				//push father node into vertex cover
				minCover.push_back(current);
			}
		}
	}
}


vector<int> GetTreeMinVertexCover (vector< vector<int> > & Graph, int start)
{
 	vector<bool> visited(Graph.size(), false);
 	vector<bool> matched(Graph.size(), false);
 	vector<int> minCover;


	//int start = 1; // any arbitrary node... really
	dfsTree(Graph, visited, matched, minCover, start);

	/*for(int i = 0; i < minCover.size(); i++)
		cout << minCover[i] << " " ;
	cout << endl;
	*/
 	return minCover;
} 

// Function : To get the no of lines in a test file
int getCNT(char * file_name)
{
	ifstream file_reader(file_name);
	
	string Line;
	int N = 0;
	while(getline(file_reader,Line))
	{	
		N++;
	}
	
	return N;
}


// Solver
void solve()
{
	char file_name[50];
	cout << "Enter the file name: " ;
	cin >> file_name;

	int N = getCNT(file_name);
	N += 1;

	vector< vector<int> >  Graph(N+1, vector<int>());

	//cout << N << " " << M << endl;

	ll x, y;
	ifstream file_reader(file_name);

	for(int i = 0; i < N-1; i++)
	{
		file_reader >> x >> y;
		Graph[x].push_back(y);
		Graph[y].push_back(x);
	}

/*
	for(int i = 1; i <= N; i++)
	{
		cout << i << " --> " ;
		for(int j = 0; j < Graph[i].size(); j++)
		{
			cout << Graph[i][j] << " ";
		}
		cout << endl;
	}
*/
	
	int start = 1;
	vector<int> RET = GetTreeMinVertexCover(Graph,start);
	cout << RET.size() << endl;
/*	for(int i = 0; i < RET.size(); i++)
		cout << RET[i] << " " ;
	cout << endl;
*/

	return;
}
 
int main()
{
	int T;
	cout << "Enter the no of test cases: " ;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
} 
