#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

#define inp_s     ios_base::sync_with_stdio(false)
#define DRT()     int test_case;cin>>test_case;while(test_case--)

#define VI        vector<int>
#define VS        vector<string>
#define VLL       vector<LL>
#define PII       pair<int,int>
#define all(c)    c.begin(),c.end()
#define sz(c)     c.size()
#define clr(c)    c.clear()
#define msi       map<string,int>
#define msit      map<string,int>::iterator
#define pb        push_back
#define mp        make_pair

#define FOR(i,a,b)      for(int i=(a);i<(b);i++)
#define RFOR(i,a,b)     for(int i=b-1;i>=a;i--)

#define gcd(a,b)  __gcd(a,b)
#define MOD       1000000007

#define GI(x)     scanf("%d",&x)
#define CASE(x)   cout<<"Case #"<<x<<": "

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};

// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
    trie_node_t *pNode = NULL;

    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));

    if( pNode )
    {
        int i;

        pNode->value = 0;

        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }

    return pNode;
}

// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, string key)
{
    int level;
    int length = sz(key);
    int index;
    trie_node_t *pCrawl;

    pTrie->count++;
    pCrawl = pTrie->root;

    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);
        if( !pCrawl->children[index] )
        {
            pCrawl->children[index] = getNode();
        }

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->value = pTrie->count;
}

// Returns non zero, if key presents in trie
int search(trie_t *pTrie, string key)
{
    int level;
    int length = sz(key);
    int index;
    trie_node_t *pCrawl;
    int ans = 1;

    pCrawl = pTrie->root;

    for( level = 0; level < length; level++ )
    {
        index = CHAR_TO_INDEX(key[level]);

        if( !pCrawl->children[index] )
            return ans;
        else ans++;

        pCrawl = pCrawl->children[index];
    }

    return length;
}

int main()
{
      int t;
      cin>>t;
      int p = 0;
      while(t--)
      {
            ++p;
            int n;
            trie_t trie;
            initialize(&trie);
            cin>>n;
            string s;
            LL ans = 0;
            FOR(i,0,n)
            {
                  cin>>s;
                  ans += search(&trie,s);
                  insert(&trie,s);
            }
            CASE(p);
            cout<<ans<<endl;
      }
}
