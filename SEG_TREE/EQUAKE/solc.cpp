
#include<bits/stdc++.h>
using namespace std;
 
#define N 800000
#define MAX 2097150// Why? :D
#define inf 0x7fffffff
template<class T>inline bool S(T &x)
{
    int c=getchar();
    int sgn=1;
    while(~c&&c<'0'||c>'9')
        {
            if(c=='-')sgn=-1;c=getchar();
        }
    for(x=0;~c&&'0'<=c&&c<='9';c=getchar())x=x*10+c-'0'; x*=sgn;
    return ~c;
}
int arr[N];
int tree[MAX][12];
int lazy[MAX];
int shift[10000][12],t,l,r,val,n,m;
/**
 * Build and init tree
 */
int rotate(int i,int v)
{
	int n[4],c=0,num=0;
	while(i!=0)
	{
		n[c]=i%10;
		i/=10;
		c++;
	}
	for(int i=c-v-1;i>=0;i--)num=num*10+n[i];
	for(int i=c-1;i>c-v-1;i--)num=num*10+n[i];
	return num;
} 
 
void build_tree(int node, int a, int b) {
  	if(a > b) return; // Out of range
  	
  	if(a == b) { // Leaf node
    	 // Init value
    		for(int i=0;i<12;i++)tree[node][i]=shift[arr[a]][i];
		return;
	}
	
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	
	for(int i=0;i<12;i++)tree[node][i] = max(tree[node*2][i], tree[node*2+1][i]); // Init root value
}
 
/**
 * Increment elements within range [i, j] with value value
 */
void update(int node,int value)
{
	value%=12;
	int t[12];
  	for(int i=0;i<12;i++)
  	    t[i]=tree[node][(i+value)%12];
  	for(int i=0;i<12;i++)
  		tree[node][i]=t[i];
}
void update_tree(int node, int a, int b, int i, int j, int value) 
{
  
  	if(lazy[node] != 0) 
  	{ // This node needs to be updated
  		update(node,lazy[node]);
   		//tree[node] += lazy[node]; // Update it
 
		if(a != b) 
		{
			lazy[node*2] += lazy[node]; // Mark child as lazy
    			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
   		lazy[node] = 0; // Reset it
  	}
  
	if(a > b || a > j || b < i) // Current segment is not within range [i, j]
		return;
    
  	if(a >= i && b <= j) 
  	{ // Segment is fully within range
    		update(node,value);
 
		if(a != b) 
		{ // Not leaf node
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}
 
    		return;
	}
 
	update_tree(node*2, a, (a+b)/2, i, j, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child
 
	for(int i=0;i<12;i++)
		tree[node][i] = max(tree[node*2][i], tree[node*2+1][i]); // Updating root with max value
}
 
/**
 * Query tree to get max element value within range [i, j]
 */
int query_tree(int node, int a, int b, int i, int j) 
{
	
	if(a > b || a > j || b < i) return -inf; // Out of range
 
	if(lazy[node] != 0) 
	{ // This node needs to be updated
		//tree[node] += lazy[node]; // Update it
 		update(node,lazy[node]);
		if(a != b) 
		{
			lazy[node*2] += lazy[node]; // Mark child as lazy
			lazy[node*2+1] += lazy[node]; // Mark child as lazy
		}
 
		lazy[node] = 0; // Reset it
	}
 
	if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node][0];
 
	int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
	int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child
 
	int res = max(q1, q2); // Return final result
	
	return res;
}
 
int main() 
{
	S(n);
	for(int i = 0; i < n; i++) 
	     S(arr[i]);
	for(int i=1;i<=9999;i++)
	{
		int d=0,n=i;
		while(n!=0){n/=10;d++;}
		for(int j=0;j<d;j++)shift[i][j]=rotate(i,j);
		for(int j=d;j<12;j++)shift[i][j]=shift[i][j%d];
	}
 	S(m);
	build_tree(1, 0, n-1);
 	for(int i=0;i<m;i++)
 	{
 		S(t);
 		S(l);
 		S(r);
 		if(t==0)
 		{
 		    S(val);
 			update_tree(1, 0, n-1, l, r, val);
 		}
 	
 		if(t==1)
 		{
 			printf("%d\n",query_tree(1, 0, n-1, l, r));
 		}
 		
 	}
 return 0;
}
 
