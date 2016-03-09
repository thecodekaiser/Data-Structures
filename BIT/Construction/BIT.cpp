#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
typedef long long ll;

// Function : TO initialize BIT
// Construction Time: O(N lg N)
ll * giveBIT(ll * ptr, int N)			// N is the length of the array ptr
{
	ll * BIT = (ll *) calloc (N+1, sizeof(ll));

	ll val;
	int k;
	for(int i = 1; i <= N; i++)
	{
		val = ptr[i];
		k = i;
		while(k <= N)
		{
			BIT[k] += val;
			k = k + (k & (-k));
		}
	}
	return BIT;
}

// Function: To get summation ptr[1] to ptr[Index]
ll GET(ll * BIT, int index)
{
	ll ans = 0;
	while (index > 0)
	{
		ans += BIT[index];
		index = index - (index & (-index));
	}
	return ans;
}

// Function : To update some value at a given index
// Example: If you want to decrease/index value at some index then get the cumulative sum
void SET(ll * BIT, ll * ptr, ll val, int index,int N)
{
	 ptr[index] += val;
	 while (index <= N)
	 {
		BIT[index] += val;
		index = index + (index & (-index));
	 }
}

// Function : To get a sum in a range.For example for Left -> Right
ll sumRange(ll * BIT, int left, int right)
{
	ll sum1 = GET(BIT, left-1);
	ll sum2 = GET(BIT, right);
	
	return sum2 - sum1;
}

// Function : To test the BIT 
void test()
{
	int N;
	cout << "Enter the no of elements in your array: " ;
	cin >> N;

	ll ptr[N+1];
	cout << "Now enter the elements: " ;
	for(int i = 1; i <= N; i++)
		cin >> ptr[i];

	int queries;
	cout << "Now enter the no of queries: ";
	cin >> queries;	
	if (queries > 1)
	{
		cout << "You can either get sum in a range or change value at some index: " << endl;;
		cout << "Enter R Left Right to get the sum of range from L to R " << endl;
		cout << "Enter S Index Val  to change value at Index" << endl;
		
		// Now create the BIT
		ll * BIT = giveBIT(ptr, N);
		char cmd;
		int left, right, index;
		ll val;
 
		while (queries--)
		{
			scanf("\n%c",&cmd);
			if(cmd == 'R')
			{
				scanf("%d %d",&left, &right);
				printf("Sum in this range is: %lld\n", sumRange(BIT, left, right));
			}
			else if(cmd == 'S')
			{
				scanf("%d %lld",&index, &val);
				SET(BIT, ptr, val, index, N);
			}
			else	
			{
				cout << "Some error occurred" << endl;
				break;
			}
		}
		free(BIT);
	}

	free(ptr);
	return;
}

// Function : Main driver function 
int main()
{
	test();
	return 0;
}
	
