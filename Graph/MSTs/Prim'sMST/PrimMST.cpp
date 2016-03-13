/** 
 * Here I am implementing the Prim's MST algorithm.
 */
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

struct edge
{
	int x, y;
	double length;
};

struct AA
{
	int x;
	double val;
};

vector<vector<pair<int, double> > > create(char * File_Name)
{
	ifstream file_reader(File_Name);
	int size, edges;
	file_reader >> size >> edges;
	vector<vector<pair<int,double> > > graph(size+1);
	int x, y;
	double cost;
	while(file_reader >> x >> y >> cost)
	{
		graph[x].push_back(make_pair(y,cost));
		//graph[y].push_back(make_pair(x,cost));
	}

	return graph;
}

vector<edge> create_edges(char * File_Name)
{
	ifstream file_reader(File_Name);
	int size, edges;
	file_reader >> size >> edges;
	vector<edge> graph;
	int x, y;
	double cost;
	edge ee1, ee2;
	while(file_reader >> x >> y >> cost)
	{
		ee1.x = x, ee1.y = y, ee1.length = cost;
		ee2.x = y, ee2.y = x, ee2.length = cost;
		graph.push_back(ee1);
		graph.push_back(ee2);
	}

	return graph;
}

int comp(edge A, edge B)
{
	if(A.length < B.length)
		return 1;
	else    return 0;
}

AA select_min_edge(int start_vertex, vector<bool> VISITED, vector<vector<pair<int,double> > > graph)
{
	AA ans;
	ans.x = -1;
	int min_edge = -1;
	double MIN_size = 100000009;
	for(int i = 0; i < graph[start_vertex].size(); i++)
	{
		if(VISITED[graph[start_vertex][i].first] == 0 && graph[start_vertex][i].second < MIN_size)
		{
			ans.val = MIN_size = graph[start_vertex][i].second;
			ans.x = graph[start_vertex][i].first;
		}
	}
	return ans;
}

double solve(int start_vertex, vector<bool> & VISITED, vector<edge> graph)
{
	cout << "CAME" << endl;
	int cnt = 1;
	double ans = 0.0;
	while(1)
	{
		double Min = 1000000007;
		int x_m;
		for(int i = 0; i < graph.size(); i++)
		{
			if(VISITED[graph[i].x] == 1 && VISITED[graph[i].y] == 0)
			{
				if(graph[i].length < Min)
				{
					Min = graph[i].length;
					x_m = graph[i].y;
				}
				VISITED[graph[i].y] = 1;
				break;
			}
		}
		cnt += 1;
		if(Min == 1000000007)
			break;
		ans += Min;
		cout << "ANS : " << ans << " MIN : " << Min <<  " Selected: " << x_m << " Cnt: " << cnt << endl;
	}

	return ans;
}
				

int main()
{
	char * ch = (char *) malloc (100 * sizeof(char ));
	printf("Enter the file name: ");
	scanf("%s",ch);
	vector<edge > graph;
	graph = create_edges(ch);
	cout << graph.size() << endl;
	int start_vertex;
	vector<bool> VISITED(501,0);

	sort(graph.begin(), graph.end(), comp);
	start_vertex = graph[0].x; 
	cout << "START: " << start_vertex << endl;
	VISITED[start_vertex] = 1;
//	for(int i = 0; i < graph.size(); i++)
//		cout << graph[i].x << "," << graph[i].y << " " << graph[i].length << endl;
	
	double val = 0.0;
	val = solve(start_vertex, VISITED, graph); 
	
	printf("MST: %lf\n", val);
	 
	return 0;
}
