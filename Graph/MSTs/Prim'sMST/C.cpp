// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MXN 505

struct edge
{
	int src, dest, len;

	edge() {}
	edge(int s, int d, int l) { src = s, dest = d, len = l; }
};

vector< edge > gph[MXN];
bool flag[MXN];
vector<edge> ans;

class comp
{
public:
	bool operator()(const edge & A, const edge & B)
	{
		return A.len > B.len;
	}
};

void solve()
{
	string file_name;
	cin >> file_name;

	ifstream file_reader(file_name.c_str());
	
	if(!file_reader.is_open())
	{
		cout << "Couldn't open the file\n" ;
		return;
	}

	string Line;
	int N = 1;
	int nVertices, nEdges;

	edge e;
	int x, y, len;

	while(getline(file_reader,Line))
	{	
		if(N == 1)
		{
			stringstream st(Line);
			st >> nVertices >> nEdges;
			//cout << nVertices << " " << nEdges << endl;
		}
		else
		{
			if(N <= nEdges+1)
			{
				stringstream st(Line);
				st >> x >> y >> len;
			//	cout << x << " " << y << " " << len << endl;
				gph[x].push_back(edge(x, y, len));
				gph[y].push_back(edge(y, x, len));
			}
		}
			
		N++;
	}


	// Now applying the Prim's algo
	priority_queue < edge, vector<edge>, comp > pq;

	pq.push(edge(1, 1, 0));

	ll sumMST = 0;
	int numEdges = 0;
	memset(flag, 0, sizeof(flag));

	while(!pq.empty())
	{
		edge temp = pq.top();	
		pq.pop();

		if(flag[temp.dest])	continue;

		//cout << temp.src << "," << temp.dest << "," << temp.len << endl;

		flag[temp.dest] = true;
		if(numEdges)
			ans.push_back(temp);

		numEdges++;
		sumMST += (temp.len);

		for(int i = 0; i < gph[temp.dest].size(); i++)
		{
			edge child = gph[temp.dest][i];

			pq.push(child);
		}
	}
	
	cout << "MST Weight: " << sumMST << " numEdges: " << ans.size() << endl;
	for(int i = 0; i < ans.size(); i++)
	{
		cout << "SRC: " << ans[i].src << " DEST: " << ans[i].dest << " LEN: " << ans[i].len << endl;
	}

	return;
}

int main()
{
	solve();
	return 0;
}
