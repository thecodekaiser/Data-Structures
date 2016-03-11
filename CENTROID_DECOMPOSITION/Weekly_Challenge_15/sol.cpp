// Author: thecodekaiser
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define INF 1000000007
#define MXN 2005

set<int> gph[MXN];
int depth[MXN], sub[MXN], label[MXN], wt[MXN], val[MXN];       
int N, M, cnt;
int dp[MXN][MXN];       // Max value taking the first i nodes and spending j value

void dfs1(int root, int pre)
{
    sub[root] = 1;
    cnt++;
    for(auto it = gph[root].begin(); it != gph[root].end(); it++)
    {
        if(*it != pre)
        {
            dfs1(*it, root);
            sub[root] += sub[*it];
        }
    }

    label[N] = root; N--;
}

int dfs2(int root, int pre)
{
    for(auto it = gph[root].begin(); it != gph[root].end(); it++)
    {
        if(*it != pre and sub[*it] > cnt/2)
            return dfs2(*it, root);
    }
 
    return root;
}

int calc(int SZ)
{
    for(int i = 0; i <= SZ; i++)
        for(int j = 0; j <= M; j++)
            dp[i][j] = -INF;

    dp[1][wt[label[1]]] = val[label[1]];

    for(int i = 2; i <= SZ; i++)
    {
        int dx = label[i];

        for(int j = 0; j <= M; j++)
        {
            if(wt[dx] <= j) dp[i][j] = max(dp[i][j], dp[i-1][j - wt[dx]] + val[dx]);

            dp[i + sub[dx] - 1][j] = max(dp[i + sub[dx] - 1][j], dp[i-1][j]);
        }
    }

    int ret = 0;
    for(int i = 0; i <= M; i++)
        ret = max(ret, dp[SZ][i]);

    return ret;
}

int do_it(int root, int tree_sz)
{
 //   cout << "root: " << root << " tree_sz: " << tree_sz << endl;
    cnt = 0;
    N = tree_sz;
    dfs1(root,root);
    N = tree_sz;
    int cen = dfs2(root,root);
    dfs1(cen, cen);

    int ret = calc(tree_sz);
 //   cout << "CEN: " << cen << " RET: " << ret << " label[1]: " << label[1] << " tree_sz: " << tree_sz << endl; 
    
    for(auto it = gph[cen].begin(); it != gph[cen].end(); it++)
    {
        gph[*it].erase(cen);
        int val = do_it(*it, sub[*it]);
        
        ret = max(ret, val);
    }

    gph[cen].clear();

    return ret;
}


void solve()
{   
    cin >> N >> M;

    int x, y;

    for(int i = 1; i <= N; i++)
        cin >> wt[i];

    for(int i = 1; i <= N; i++)
        cin >> val[i];

    for(int i = 0; i < N-1; i++)
    {
        cin >> x >> y;
        gph[x].insert(y);
        gph[y].insert(x);
    }

    cout << do_it(1, N) << endl;

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