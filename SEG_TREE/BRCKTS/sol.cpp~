// Author: thecodekaiser
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct data {
	int open, close;
};

data make_data(int val)
{
	data res;
	if(val == 1)
		res.open = 1, res.close = 0;
	else
		res.open = 0, res.close = 1;

	return res;
}

data combine(data A, data B)
{
	data res;
	int mi = min(A.open, B.close);
	res.open = A.open + B.open - mi;
	res.close = A.close + B.close - mi;
	return res;
}

template <typename T> class SEG {

private:
	T * copyArr;
	data * tree;
	int len;

	// Build
	void build(int Node, int l, int r)
	{
		if(l == r)
			tree[Node] = make_data(copyArr[l]);

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;

			build(left, l, mid);
			build(right, mid+1, r);

			tree[Node] = combine(tree[left], tree[right]);
		}
	}

	// Updation
	void update(int Node, int l, int r, int i, int val)
	{
		if(l == r)
			tree[Node] = make_data(val);

		else
		{
			int left = 2 * Node, right = 2 * Node + 1, mid = (l+r)/2;
	
			if(i <= mid)
				update(left, l, mid, i, val);
			else
				update(right, mid+1, r, i, val);

			tree[Node] = combine(tree[left], tree[right]);
		}
	}

public: 
	// Constructor
	SEG(T * arr, int N)
	{
		len = N;
		copyArr = (T *) malloc (len * sizeof(T));
		tree = (data *) malloc (4*len * sizeof(data));

		for(int i = 0; i < len; i++)	copyArr[i] = arr[i];

		build(1, 0, len-1);

//		for(int i = 1; i <= 13; i++)
//			cout << "i: " << i << " Balance: " << tree[i].balance << " CL: " << tree[i].cl_req << ",OP: " << tree[i].op_req << endl;
	}

	// Updation
	void update(int i, int val)
	{
		copyArr[i] = val;
		update(1, 0, len-1, i, val);
		
//		for(int i = 1; i <= 13; i++)
//		cout << "i: " << i << " Balance: " << tree[i].balance << " CL: " << tree[i].cl_req << ",OP: " << tree[i].op_req << endl;
	}

	// Query
	void query()
	{
		if(tree[1].close == 0 and tree[1].open == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
	
};

int main()
{
	int test = 10;
	for(int k = 1; k <= test; k++)
	{ 
		int N, Q, cmd,val;
		char ch;
		scanf("%d\n",&N);

		int ptr[N];
		char arr[N];
		scanf("%s",arr);

		for(int i = 0; i < N; i++)
		{	ch = arr[i];
			if(ch == '(') ptr[i] = 1;
			else ptr[i] = -1;  
		}

		/*
		for(int i = 0; i < N; i++)
			cout << ptr[i] << " " ;
		cout << endl;
		*/

		SEG<int> st = SEG<int>(ptr,N);

		scanf("%d",&Q);
		printf("Test %d:\n",k);
		for(int i = 0; i < Q; i++)
		{
			scanf("%d",&cmd);
			if(cmd == 0)
			{
				st.query();
			}
			else
			{
				val = ptr[cmd-1];
				val = 0-val;
				ptr[cmd-1] = val;

				st.update(cmd-1, val);
			}
		} 
	}
	return 0;
}
