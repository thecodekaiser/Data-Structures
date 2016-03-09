/*	
* A min-max heap is pretty much the same like a max-priority(min) queue
* but just a little different in implementation.
* It not only allows to get us the max(min) element in constant time but
* also allows us to delete the max(min) logarithmic time.
* We can also use it for finding the k^th order statistic in an array in 
* constant time.
* Construtction time : O(n)
* Max/Min element    : O(1)
* DelMax/DelMin      : O(lg n)
* Note : We check the level by lg(i)		where lg is binary logarithm
* 
* Here I am implementing the min-max heap which has min-level at even level and
* max at odd level i.e  a node is minimum than all it's children if it's at an even level
* and opposite for odd level.
* Credits : M. D. ATKINSON, J.R. SACK, N. SANTORO, and T. STROTHOTTE, 1986
* Author : thecodekaiser
*/


#include <bits/stdc++.h>

using namespace std;

#define INF 1000000

class QueueEmptyException
{
public:
	QueueEmptyException()
	{
		cout << "Queue is already empty" << endl;
	}
};

template <class A_Type> class MinMaxQ
{
	// Declaring the array which we use as the heap
public:
			A_Type * heap;
			int count;			// To keep an account of the total elements in the heap
			int N;				// To keep an account of the next availabe position
			int sz;				// To keep an account of the current size of the heap

	// Our constructor
public:
		MinMaxQ <A_Type> ()
		{
			heap = (A_Type *) calloc (2 , sizeof(A_Type));	// Initital size of the heap is 2 we use array resizing as we need
			sz = 2;
			N = 0;						// Array filling starts from the position 1
			count = 0;
		}

	
/*****************************************
*	   Helper Methods		 *
*****************************************/

private:	
	// Function: To help in the resizing procedure
	void resize(int capacity)
	{
		A_Type * copy = (A_Type *) calloc (capacity , sizeof(A_Type));
		int i ;
		for (i = 0; i < sz ; i++)
		{
			copy[i] = heap[i];				// Copy over the values
		}
		sz = capacity;						// Change the capacity 
		free(heap);							// Delete the earlier version
		heap = copy;						// Assign to the newly created version
	}


	// Function: To give the index of the smallest among the children and grand-children(if any) of heap[i]
	// We are assuming that heap[i] has children i.e. 2*i <= N
	// Now we need to find if heap[i] has grandchildren
	int min_i(int i)
	{
		// Define the min and min_index
		A_Type min = INF;			 // Initialise Min to be INF
		int min_index = i;
		int j = 2*i;
		if (heap[j] < min)
			min = heap[j]  , min_index = j;
		if (j < N && heap[j] > heap[j+1])
			min = heap[j+1], min_index = j+1;

		if(2*j <= N)
		{
			int k = 2*j;		// Here k -> 2*(j)
			if(heap[k] < min)
				min = heap[k]  , min_index = k;
			if(k < N && heap[k] > heap[k+1])   
				min = heap[k+1], min_index = k+1;
		}

		if(2*(j+1) <= N)
		{
			int k = 2*(j+1);	// Here k -> 2*(j+1)
			if(heap[k] < min)
				min = heap[k]  , min_index = k;
			if(k < N && heap[k] > heap[k+1])	
				min = heap[k+1], min_index = k+1;
		}

		// Now we have got our min_index so let's just return it
		return min_index;
	}

	// Function: To give the index of the largest among the children and grand-children(if any) of heap[i]
	// We are assuming that heap[i] has children i.e. 2*i <= N
	// Now we need to find if heap[i] has grandchildren
	int max_i(int i)
	{
		// Define the max and max_index
		A_Type max = 0;					  // Initialise Max to be INF
		int max_index = i;
		int j = 2*i;
		if (heap[j] > max)
			max = heap[j]  , max_index = j;
		if (j < N && heap[j] < heap[j+1])
			max = heap[j+1], max_index = j+1;

		if(2*j <= N)
		{
			int k = 2*j;		// Here k -> 2*(j)
			if(heap[k] > max)
				max = heap[k]  , max_index = k;
			if(k < N && heap[k] < heap[k+1])
				    max = heap[k+1], max_index = k+1;
		}

		if(2*(j+1) <= N)
		{
			int k = 2*(j+1);	// Here k -> 2*(j+1)
			if(heap[k] > max)
				max = heap[k]  , max_index = k;
			if(k < N && heap[k] < heap[k+1])
				max = heap[k+1], max_index = k+1;
		}

		// Now we have got our max_index so let's just return it
		return max_index;
	}

private:
	// Function: To help sinking down from a min-level
	// We need to compare with both children and the grandchildren
	void sink_min(int i)
	{
		if(2*i <= N)	// If heap[i] has children then
		{
			// Let m be the index of smallest of heap[i] ' s children and grandchildren (if any)
			int m = min_i(i);
			// If heap[m] is a grandchild then 
			if(m > 2*(i+1))
			{
				if(heap[m] < heap[i])
				{
					swap(heap[m],heap[i]);
					if(heap[m] > heap[m/2])		// If after swapping heap[m] is bigger than its parent
						swap(heap[m], heap[m/2]);
					sink_min(m);
				}
			}
			else		// If heap[m] is a child of heap[i]
			{
				if(heap[m] < heap[i])
					swap(heap[m],heap[i]);
			}
		}
	}

private:
	// Function: To help sinking down from a min-level
	// We need to compare with both children and the grandchildren
	void sink_max(int i)
	{
		if(2*i <= N)		// If heap[i] has children then
		{
			// Let m be the index of greatest of heap[i] ' s children and grandchildren (if any)
			int m = max_i(i);
			// If heap[m] is a grandchild then 
			if(m > 2*(i+1))
			{
				if(heap[m] > heap[i])
				{
					swap(heap[m],heap[i]);
					if(heap[m] < heap[m/2])		// If after swapping heap[m] is smaller than its parent
						swap(heap[m], heap[m/2]);
					sink_max(m);
				}
			}
			else		// If heap[m] is a child of heap[i]
			{
				if(heap[m] > heap[i])
					swap(heap[m],heap[i]);
			}
		}
	}


private:
	// Function: To help in the sink procedure
	// We need to keep in mind that we have to maintain both orderings
	void sink(int i)				// i is a position in the array
	{
		if ((int)(log10(i+0.0)/log10(2.0))   %   2 == 1) 	// Max on odd level
			sink_max(i);
		else		   					// Min on even level
			sink_min(i);
	}

private:
	// Function : To help up in  the swim procedure at min-level
	void swim_min(int i)
	{	
		if(i > 3)			 // heap[i] has a grandparent
		{
			if(heap[i] < heap[i/4])	 // If it is smaller than its grandparent then it needs to go up in the heap
			{
				swap(heap[i],heap[i/4]); 
				swim_min(i/4);	 // Follow the procedure for the grandparent
			}
		}
	}

	// Function : To help up in  the swim procedure at max-level
private:
	void swim_max(int i)
	{	
		if(i > 3)			// heap[i] has a grandparent
		{
			if(heap[i] > heap[i/4])	// If it is larger than its grandparent then it needs to go up in the heap
			{
				swap(heap[i],heap[i/4]);
				swim_max(i/4);		// Follow the procedure for the grandparent
			}
		}
	}

	// Function : To help in the actual swim procedure
private:
	void swim(int i)
	{	
		// If i is on a min-level
		if((int)(log10(i+0.0)/log10(2.0))   %   2 == 0)
		{
		//	cout << "min" << endl;	
			// If heap[i] has a parent and greater than its parent
			if(i > 1 && heap[i] > heap[i/2])
			{		swap(heap[i],heap[i/2]),	swim_max(i/2);		}
			else
			{		swim_min(i);		}
		}
		else					// If i is on a max-level
		{	
		//	cout << "max" << endl;
			// If heap[i] has a parent and smaller than its parent
			if(i > 1 && heap[i] < heap[i/2])
			{		swap(heap[i],heap[i/2]),	swim_min(i/2);		}
			else
			{		swim_max(i);		}
		}
	}

/****************************************************************************/

	// Function : To insert into the heap
public:
	void insert(A_Type h)
	{
		if((N+1) == sz)
			resize(sz*2);

		heap[++N] = h;
		swim(N);
	}

	// Function : To get the min 
	A_Type min()
	{
		return heap[1];
	}	
	
	// Function : To get the max
	A_Type max()
	{ 
		if(heap[2] > heap[3])	return heap[2];
		else			return heap[3];
	}

	// Function : To get the current size
	int size()
	{
		return sz;
	}

	// Function :  To help in the deletion operation 
	// Returns max element in the heap and deletes it and maintains the heap order
	A_Type delMax()
	{
		// Check if there is no element at all in the heap
		if(N == 0)
			throw new QueueEmptyException();

		// Check if there is only one element in the heap
		if(N == 1)
		{
			A_Type M = heap[N--];
			heap[N+1] = NULL;
			return M;
		}
		else
		{
			if ((N+1) == (sz/4))
				resize(sz/2);
			int i;
			if(heap[2] > heap[3]) i = 2;
			else		      i = 3;
			A_Type M = heap[i];
			swap(heap[i],heap[N--]);
			heap[N+1] = NULL;
			sink(i);
		}
	}

	// Function :  To help in the deletion operation 
	// Returns min element in the heap and deletes it and maintains the heap order
	A_Type delMin()
	{
		// Check if there is no element at all in the heap
		if(N == 0)
			throw new QueueEmptyException();

		if ((N+1) == (sz/4))
				resize(sz/2);
		A_Type M = heap[1];
		swap(heap[1], heap[N--]);
		heap[N+1] = NULL;
		sink(1);
		return M;
	}
};

int main()
{
	MinMaxQ<long> q;
	q.insert(25);
	q.insert(37);
	q.insert(80);
	q.insert(65);
	q.insert(12);
	
	
	for(int i = 1; i < q.size(); i++)		cout << q.heap[i] << " " ;
	cout << endl;
	cout << q.max() << " " << q.min() << endl;;
	q.delMax();
	q.delMin();
	cout << q.max() << " " << q.min() << endl;	
	for(int i = 1; i < q.size(); i++)		cout << q.heap[i] << " " ;
	cout << endl;

	return 0; 
}
