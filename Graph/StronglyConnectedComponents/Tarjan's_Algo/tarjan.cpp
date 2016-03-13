/**
 * This code implements the Tarjan's Algorithm to find out the 
 * Strongly-Connected Components of a graph.
 * 
 * Author: thcodekaiser
 */

#include <bits/stdc++.h>

using namespace std;

/**
 *  Function: To get the highest node appearing in test data
 *  Read in the file and return the required  no of total nodes in the graph.
 *  Note : This gives the highest node encountered in the file.
 */
long getCNT(char * File_Name)
{
	// Open the file and keep track of the higest node encountered
	ifstream fin(File_Name);
	
	long Node = 0;
	long MaxNode = 0;

	while(fin)
	{
		// Check the node value
		fin >> Node;
		
		if(Node > MaxNode)
		{
			MaxNode = Node;
		}
	
		// Check the outgoing node value
		fin >> Node;	
				
		if(Node > MaxNode)
		{
		  	MaxNode = Node;
		}
	}
	
	return MaxNode;
}


/**	
 *  Function : To construct the graph
 *  Read in the file and construct the graph.
 */
vector< vector<long> > makeGraph(char * File_Name)
{
	long nodes = getCNT(File_Name);

	//cout << "CNT: " << nodes << endl;

	// Here is the graph
	vector< vector<long> > graph(nodes+1);

	// Opening the file
	ifstream fin(File_Name);
	long Node;			// This is the value in the first column. It denoted the tail of the edge b/w Node & outGoing
	long outGoing; 			// This is the value in the second column. It denotes the head of the edge b/w Node & outGoing
	while(fin >> Node >> outGoing)
	{

		// Assign y to x's adjacency list. That is add an outgoing edge to x's list
		graph[Node].push_back(outGoing);
	}

	return graph;
}


// Global Variable
long IND;

/**
 * This here is the dfs function
 */
void strongConnect(map< long, vector<long> > & SCC, vector<long> & index, vector<long> & lowLink, stack<long> & S, const vector< vector<long> > & graph, long V, vector<bool> & explored, vector<bool> & inStack)
{
	// Set the depth index for V to the smallest unused index
	
	explored[V] = true;
	index[V]    = IND;
	lowLink[V]  = IND;
	S.push(V);				// Push to stack
	inStack[V]  = true;		// Set true for stack 
	IND = IND + 1;			// Increase unused index
	

	// Consider the succesor of V	
	vector<long>::const_iterator it;

    for (it = graph[V].begin(); it != graph[V].end(); it++)
	{
        	// Recursively call DFS if not explored
		if (!explored[*it]) {
			
			// Successor has not been explored, recurse on it		    
			strongConnect(SCC, index, lowLink, S, graph, *it, explored, inStack);
			lowLink[V] = min(lowLink[V], lowLink[*it]);
		}
		else if(inStack[*it])   // If this visited node is in the stack
		{
			// Succesor is in the stack and hence in the current SCC
			lowLink[V] = min(lowLink[V], index[*it]);
		}
    }

	// If V is the root of the current SCC then output the stack
	if (lowLink[V] == index[V])
	{
		//cout << "Right now top element of stack: " << S.top() << "\n";
		while(S.top() != V)
		{
			inStack[S.top()] = false;
			SCC[V].push_back(S.top());
			S.pop();
			
		}
		SCC[V].push_back(S.top());
		inStack[S.top()] = false;
		reverse(SCC[V].begin(), SCC[V].end());
		S.pop();
	}
}

/**
 * This is the Tarjan's Algorithm
 */
map< long, vector<long> > tarjan(const vector< vector<long> > & graph)
{
	IND = 1;
	vector<bool> explored(graph.size(),0);
	vector<long> index(graph.size(),0);
	vector<long> lowLink(graph.size(),0);
	vector<bool> inStack(graph.size(),0);

	stack<long> S;
	map< long, vector<long> > SCC;
	
	//cout << "Starting: " << endl;

	/*for(int i = 0; i < graph.size(); i++)
		cout << "Index[i]: " << index[i] << " explored[i]: " << explored[i] << " lowLink[i]: " << lowLink[i] << endl;
	*/

	for(int i = 1; i < graph.size(); i++)
	{
		if(explored[i] == false)
		{
			//cout << "Starting DFS on: " << i << endl;
			strongConnect(SCC, index, lowLink, S, graph, i, explored, inStack);
		}
	}
	
	return SCC;
}


// Function : That calls Tarjan's algo
void giveSCC(const vector< vector<long> > & graph)
{
	map< long, vector<long> > SCC = tarjan(graph);

	map< long, vector<long> >::const_iterator it;
    	for (it = SCC.begin(); it != SCC.end(); it++) {
		cout << it->first << " --> " ;
		for(int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " " ;
		cout << endl;
	}

	return ;
}

// Main driver to test above functions
void do_it()
{
	// Ask for the file name
	char * ch = (char * ) malloc(100 * sizeof(char));
	printf("Please enter the file name: ");
	scanf("%s",ch);

	// Create graph
	vector< vector<long> > graph = makeGraph(ch);
	cout << "GRAPH CREATED" << endl;
    cout << graph.size() << endl;
	for(int i = 1; i < graph.size(); i++)
	{
		cout << i << " --> ";
		for(int j = 0; j < graph[i].size(); j++)
			cout << graph[i][j] << " " ;
		cout << endl;
	}

	// Get the SCCs from the graph
	giveSCC(graph);

	return;
}
	

int main()
{
	do_it();
	return 0;
}
