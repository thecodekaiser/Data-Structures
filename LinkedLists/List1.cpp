/**
 * This code implements an implementation of a linked list.
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
#define nLine	cout << endl

// Defining node structure
struct Node
{
	int Key;
	Node * Next;
};

// Defining exception class
class EmptyListException
{
public : 
	// Constructor
	EmptyListException(string message)
	{
		cout << message << endl;
	}
};

// Defining the Linked List class
class LinkedList
{

private:
	// Private variables of the class
	Node * head, * last;			// Head node of the list
	int N;							// N --> Count of elements in the list


	// Function : To insert into the list from head
	void pushAtHead(int DATA)
	{
		// Create a new node
		Node * temp = (Node *) malloc (sizeof(Node));
		temp -> Key = DATA;
		temp -> Next = NULL;
		
		// Change the links
		temp -> Next = head;
		head = temp;
		if(isEmpty())
		{
			last  = temp;
		}
		// Increase the count
		N++;
		return;
	}

	// Function : To insert into the list from head
	void pushAtEnd(int DATA)
	{
		// Create a new node
		Node * temp = (Node *) malloc (sizeof(Node));
		temp -> Key = DATA;
		temp -> Next = NULL;

		// Change the links
		if(isEmpty())
		{
			last = head = temp;
		}
		else
		{
			last -> Next = temp;
			last = temp;
		}		
		// Increase the count
		N++;
		return;
	}

	// Function : To delete all occurrences of a particular data from a linked list
	// If parameter for all is 0 then it deletes only the first one from the head else all occurrences 
	void del(Node ** first,Node ** last, int DATA, int all = 0)
	{

		if((*first) == NULL)
			return;			// If list is empty then go back
		
		Node * prev, * temp, * curr;

		int flag = 0;			// To know if a value has been deleted
		// While you get this value at head keep on deleting
		while((*first) -> Key == DATA)
		{
			temp = (*first);
			(*first) = (*first) -> Next;
			free(temp);
			N--;
			if(all == 0)
				return;
		} 
		// Now we have deleted all nodes from the starting that have a value equal to DATA
		prev = (*first);
		if(N == 1)
		{
			if(prev -> Key == DATA)
			{
				temp = prev;
				prev = prev -> Next;
				free(temp);
				N--;
				flag = 1;
			}
		}
		else
		{
			curr = prev -> Next;
			while(curr != NULL)
			{
				if(flag == 1 && all == 0)
					break;

				if(curr -> Key == DATA)
				{
					// Need to delete this node
					temp = curr;
					curr = curr -> Next;
					prev -> Next = curr;
					N--;
					free(temp);
					flag = 1;

					// Special consideration to update the last pointer 
					if(curr == NULL)
					{
						// Then p is the new last pointer
						(* last) = prev;
					}
				}
				else
				{
					prev = curr;
					curr = curr -> Next;
				}
			}
		}

		prev = temp = curr = NULL;
		free(prev), free(temp), free(curr);		// Delete unused memory

		return;					       // Return 	
	}

	// Function : To print the list starting at a given node
	void printAtNode(Node * first)
	{
		//cout << "THIS IS HEAD: " << first -> Key << endl;
		Node * curr = first;
		while(curr != NULL)
		{
			cout << curr -> Key << " ";
			curr = curr -> Next;
		}
		cout << endl;
		free(curr);		// Avoid memory leakage
	}

	// Function : To reverse a linked list recursively
	Node * recur_reverse(Node * first)
	{

		// Here we must consider 3 cases
		// Base Case: The list is empty
		if(first == NULL)
		{
	//S		cout << "First: " << first -> Key << endl;
			return first;
		}
		else if(first -> Next == NULL)
		{
			// Base Case: The list has only one element
	//		cout << "First: " << first -> Key << endl;
			return first;
		}
		else
		{
			// Means that the list has atleast two elements
			Node * Second = first -> Next;
			
			
	//		cout << "First: " << first -> Key << " Second: " << Second -> Key << endl;
			Node * ReverseSet = recur_reverse(Second);
	//		cout << "ReverseSet: " << ReverseSet -> Key << endl;
			Second -> Next = first;
			first -> Next = NULL;
	//		cout << "First: " << first -> Key << " Second: " << Second -> Key << " Second.Next: " << Second -> Next -> Key << endl;

	//		printAtNode(ReverseSet);
			return ReverseSet;
		}
	}

	// Function : To get the middle node
	Node * middleNode(Node * first)
	{
		if(isEmpty())
			throw new EmptyListException("List is empty");

		if(count() == 1)
		{
			return first;
		}
		else
		{
			Node * slow, * fast;
			slow = first;
			fast = slow -> Next;		// Make appropriate connections

			while(fast != NULL)
			{
				fast = fast -> Next;
				if(fast != NULL)
				{
					fast = fast -> Next;
					slow = slow -> Next;
				}
			}
			free(fast);
			return slow;
		}
	}

	// Function : To reverse a list upto a given node only
	Node * recur_reverse_limit(Node * first, Node * limit)
	{
		// Base Case: The list is empty
		if(first == NULL)
			return first;
		else if(first -> Next == NULL)
		{
			// Single element list
			return first;
		}
		else if(N % 2 == 0 && first == limit)
		{
			return first;			// If the length is even then we till the mid pointer
		}
		else if(N % 2 == 1 && first -> Next == limit)
		{
			return first;			// Else we stop one short of it
		}
		else
		{
			Node * temp;
			Node * second =	second = first -> Next;

			Node * ReverseSet = recur_reverse_limit(second,limit);

			temp = second -> Next;				// Store the next link of the limit node
			first -> Next = temp;				// Point first to this node0
			second -> Next = first;				// Point second to first
			
			printAtNode(ReverseSet);
			return ReverseSet;
		}
	}

	// Function : To reverse a list upto a given node only
	Node * recur_reverse_Upto(Node * first, Node * limit)
	{
		// Base Case: The list is empty
		if(first == NULL)
		{
			return first;
		}
		else if(first -> Next == NULL)
		{
			// Single element list
			return first;
		}
		else if(first == limit)
		{
			return first;			// If the length is even then we till the mid pointer
		}
		else
		{
			Node * temp;
			Node * second =	 first -> Next;

			Node * ReverseSet = recur_reverse_Upto(second,limit);
			
			temp = second -> Next;				// Store the next link of the limit node
			first -> Next = temp;				// Point first to this node
			second -> Next = first;				// Point second to first
			
			return ReverseSet;
		}
	}


	// Function : Iterative reversal of a linked list
	void iter_reverse(Node ** first, Node ** last)
	{
		Node * curr = (* first);
		Node * tLast = ( * first);
		Node * prev = NULL;
		Node * next = NULL;
		while(curr != NULL)
		{
			next = curr -> Next;
			curr -> Next = prev;
			prev = curr;
			curr = next;
		}
		
		(*first) = prev;
		(*last)  = tLast;
		
		return;
	}

	// Function : To reverse a linked list in chunks of size k
	Node * reverseK(Node * first, int K)
	{
		Node * curr = first;	
		Node * prev = NULL;
		Node * next = NULL;
		int count = 0;

		while(curr != NULL && count < K)
		{
			next = curr -> Next;
			curr -> Next = prev;
			prev = curr;
			curr = next;
			count++;
		}
		
		// next points to the (k+1)th node now
		if(next != NULL)
		{
			first -> Next = reverseK(next,K);
		}

		return prev;
	}


	// Function : To segregate even and odd nodes in a linked list
	void segregate(Node ** first, Node ** last)
	{
		
		Node * new_end, * end, * prev, * curr;
		end = (*first);
		prev = NULL;
		curr = (*first);

		// Get the pointer to the last node
		while(end->Next != NULL)
			end = end -> Next;

		new_end = end;
		
		//cout << "D1" << endl;
		// Consider moving all odd nodes before the first even nodes to the end of the list
		while(curr->Key % 2 != 0 && curr != NULL)
		{
			new_end -> Next = curr;
			curr = curr -> Next;
			new_end -> Next -> Next = NULL;	
			new_end = new_end -> Next;
		}
		//cout << "D2" << endl;
		// Now we have an even node or all nodes have been exhausted
		if(curr -> Key % 2 == 0)
		{
			(*first) = curr;
			
			while(curr != end)
			{
		//		cout << curr->Key << endl;
				if(curr -> Key % 2 == 0)
				{	
					prev = curr;
					curr = curr -> Next;
		 		}
				else
				{
					prev -> Next = curr -> Next;
					curr -> Next = NULL;
					new_end -> Next = curr;
					new_end = curr;
					curr = prev -> Next;
				}
				
			}
		}

		else prev = curr;		// All are odd only

		//cout << "D3" << endl;
		//printAtNode(*first);
		 /* If there are more than 1 odd nodes and end of original list is
     	            odd then move this node to end to maintain same order of odd
                    numbers in modified list */
	        if (new_end != end && (end -> Key)%2 != 0)
		{
		      prev -> Next = end -> Next;
		      end -> Next = NULL;
		      new_end -> Next = end;
		}

		(*last) = end;

		return;
	}

		

	// Function : To swap K-th node from beginning with the k-th node from end
	void swap_Kth(Node ** first,Node ** last, int len, int K)
	{
		// First check if K is in bounds
		if(K > len)
			return;			// If K > len then go out
		
		if((N&1) == 1 && K == (N/2 + 1))
			return;			// Same nodes to be changed

		if(len == 1)
			return;			// Length is only one

		if(K == 1 || K == len)
		{
			// Means that we have to interchange the last and the first nodes in the list
			Node *p1, * c1, * p2 , * c2, * temp;
			c1 = p2 = c2 = (*first);

			// Traverse and go to the last node
			int i = 0;
			while(i != len-1)
			{ p2 = c2 ; c2 = c2 -> Next; i++; }
		
			
			// Now we have first node and second node both 
			p1 = c1 -> Next;
			p2 -> Next = c1;
			c1 -> Next = NULL;
			c2 -> Next = p1;

			(*first) = c2;
			(*last)  = c1;

			temp = c1 = p1 = c2 = p2 = NULL;
			free(temp), free(c1), free(c2), free(p1), free(p2);
		}
		/*else if((N&1) == 0 && (K == N/2))
		{
			// Nodes are next to each other
			Node *p1, * c1, * c2, * temp;
			c1 = p1 = (* first);			// We don't need p2 
			c2 = (c1 -> Next);
			
			// Traverse till you reach the destination 
			int i = 1;
			while(i != K)
			{
				p1 = c1;
				c1 = c1 -> Next;
				c2 = c2 -> Next;
				i++;
			} 

			// Now we have both c1 and c2
			temp = c2 -> Next;
			p1 -> Next = c2;
			c2 -> Next = c1;
			c1 -> Next = temp;
			
			temp = c1 = p1 = c2 = NULL;
			free(temp), free(c1), free(c2), free(p1);
		}*/
		else
		{
			// They are not next to each other
			// Here we need total six nodes in all 
			// One curr, one prev, one next for each position
			Node * c1, * c2 , * p1, * p2;

			c1 = c2  = (* first);
			int lo, hi;

			int i = 1;
			if(K > N/2)
			{
				lo = N - K + 1;
				hi = K;
			}
			else
			{
				lo = K;
				hi = N-K+1;
			}

			// Get the first pointer
			while(i != lo)
			{
				p1 = c1;
				c1 = c1 -> Next;
				p2 = c2;
				c2 = c2 -> Next;
				i++;
			}

			// Now we have our first pointer
			// Let's get the second one
			while(i != hi)
			{
				p2 = c2;
				c2 = c2 -> Next;
				i++;
			}

			Node * temp1, * temp2;
	
			temp1 = c1 -> Next, temp2 = c2 -> Next;
			
			p1 -> Next = c2;
			if(c2 != temp1)
				c2 -> Next = temp1;
			else
			   	c2 -> Next = c1;
		
			if(p2 != c1)
				p2 -> Next = c1;
			
			c1 -> Next = temp2;
	
			temp1 = c1 = p1 = c2 = p2 = temp2 = NULL;
			free(c1), free(c2), free(p1), free(p2), free(temp1), free(temp2);
		}	
	}
		

	/* Function : To remove loop given the head of list and a node in the loop				
	 * 	      loop_node --> Pointer to one of the loop nodes
 	 *	      head -->  Pointer to the start node of the linked list
	 */
	void removeLoop(Node * loop_node, Node * head)
	{
	   Node * ptr1;
	   Node * ptr2;
	 
	   /**
	    *  Set a pointer to the beging of the Linked List and
	    *  move it one by one to find the first node which is
	    *  part of the Linked List 
	    */
	   ptr1 = head;
	   while(1)
	   {
	     /* Now start a pointer from loop_node and check if it ever
	        reaches ptr2 */
	     ptr2 = loop_node;
	     while(ptr2 -> Next != loop_node && ptr2 -> Next != ptr1)
	     {
		 ptr2 = ptr2 -> Next;
	     }
	 
	     /* If ptr2 reahced ptr1 then there is a loop. So break the
		loop */
	     if(ptr2 -> Next == ptr1)
		break;
	 
	     /* If ptr2 did't reach ptr1 then try the next node after ptr1 */
	     else
	       ptr1 = ptr1 -> Next;
	   }
	 
	   /* After the end of loop ptr2 is the last node of the loop. So
	     make next of ptr2 as NULL */
	   ptr2 -> Next = NULL;
	}

	/**
	 * This function detects and removes loop in the list
  	 * If loop was there in the list then it returns 1,
  	 * otherwise returns 0 
	 * It essentially uses the Floyd's Hare and Tortoise Algorithm
	 */
	int loopCheck(Node * first)
	{
	    Node  * slow_p = first, * fast_p = first;
	 
	    while (slow_p && fast_p && fast_p -> Next)
	    {
		slow_p  = slow_p -> Next;
		fast_p  = fast_p -> Next -> Next;
	 
		/* If slow_p and fast_p meet at some point then there
		   is a loop */
		if (slow_p == fast_p)
		{
		    removeLoop(slow_p, first);
	 
		    /* Return 1 to indicate that loop is found */
		    return 1;
		}
	    }
 
    		/* Return 0 to indeciate that ther is no loop*/
    		return 0;
	}
	
public:
	// Constructor
	LinkedList()
	{
		head = last = NULL;
		N    = 0;
	}

	// Function : To check if the list is empty
	bool isEmpty()
	{
		return N == 0;
	}

	// Function : To give the count of elements in the list
	int count()
	{
		return N;
	}

	// Function : To insert at the head of the list
	// 	      Works as if inserting in a stack
	void pushHead(int DATA)
	{
		pushAtHead(DATA);
		return;
	}

	// Function : To insert at the end of the list
	// 	      Works as if inserting in a stack
	void pushEnd(int DATA)
	{
		pushAtEnd(DATA);
		return;
	}

	// Function : To print the list
	void print()
	{
		printAtNode(head);
		return;
	}

	// Function : To reverse a list
	void reverse()
	{
		head = recur_reverse(head);
		return;
	}

	// Function : To reverse a list only till middle
	void reverse_mid()
	{
		Node * temp = middleNode(head);
		head = recur_reverse_limit(head,temp);
		temp = NULL;
		free(temp);		// Avoid memory leakage
		return;
	}

	// Function : To show the middle element
	void middle()
	{
		Node * temp = middleNode(head);
		cout << "Middle element: " << temp -> Key << endl;
		temp = NULL;
		free(temp);		// Avoid memory leakage
		return;
	}

	// Function : To check if a liked list is palindromic or not
	void checkPalin()
	{
		reverse_mid();
		
		Node * curr2 = middleNode(head);		
	
		Node * curr1 = head;
		curr2 = curr2 -> Next;		// Move Middle one pointer ahead
		int flag = 0;
	
		while(curr2 != 0)
		{
			if(curr2 -> Key != curr1 -> Key)
			{ flag = 1; break; }
			curr2 = curr2 -> Next;
			curr1 = curr1 -> Next; 	
		}

		curr2 = curr1 = NULL;			// Free memory to avoid memory leakage
		free(curr1), free(curr2);

		if(flag)
			cout << "Not palindromic" << endl;
		else	cout << "Palindromic" << endl;

		reverse_mid();
	
		return;
	}

	// Function : To reverse elements of a given linked list in pairs of K elements
	void swapK_Pairs(int len, int K)
	{
		
		// First check if the current length is less than the parameter K
		// If yes then reverse the whole list
		if(len <= K)
		{
			// Reverse the whole list and exit
			reverse();
		}
		else
		{
			// We can do atleast one complete reversal of a K-Pair
			// Ok so let's do it
			// Traverse upto K th element
			int i = 0; 
			Node * curr1, * curr2, * prev, * temp;
			prev = head;
			curr1 = prev;		// Initially both prev and curr point to same head
			while(i != K-1)
			{
				curr1 = curr1 -> Next;
				i++;
			}

			len -= K;
			
			// Now make a reversal for the first K-Pair
			head = recur_reverse_Upto(prev,curr1);		// Done

			// Now check if we can still do any reversals
			// But we must know that after reversing we must link it to the remaining list
			if(len > 0 && len > K)
			{
				// This is the case that I find a little tricky
				// Now set prev and curr2 as the next of curr1
				while(len > K)
				{
					// Set the curr1 and curr2 pointer
					curr1 = curr2 = prev -> Next;
					
					i = 0; 
					while(i != K-1)
					{
						curr2 = curr2 -> Next;	
						i++;
					}
					
					// Get the link of the partial reversed list
					temp = recur_reverse_Upto(curr1,curr2);
					
					prev -> Next = temp;		// Link it to the previous pointer
					prev = curr1;			// Update previous

					len -= K;			// Decrease the length
				}

				// Now after coming out check again if some part is left
			
				prev = curr1 -> Next;			// Set the previous pointer
				if(len > 0)
				{
					// There is a part remaining that needs to be reversed
					prev = recur_reverse(prev);		// Get the reversed link
					curr1 -> Next = prev;			// Link it to the rest of the list
					len -= K;				// Decrease the length
				}
			}
			else if (len > 0)
			{
				// Either len is < k or it is = K
				// So do a reversal here
				curr2 = prev -> Next;
				curr2 = recur_reverse(curr2);
				prev -> Next = curr2;
				len -= K;
			}

			// Now free the memory
			prev = NULL, curr1 = NULL, curr2 = NULL, temp = NULL;
			free(prev), free(curr1), free(curr2), free(temp);
		}
						
	}

	// Improved function to reverse a list in chunks
	void revK(int K)
	{
		head = reverseK(head,K);
		return;
	}

	// Function : To delete a particular element from a linked list
	void deleteN(int DATA)
	{
		int choice ;
		cout << "Do you want to delete all occurrences or all the occurrences from the list? Press 0 for first one and 1 for all: " ;
		cin >> choice;
		del(&head,&last, DATA,choice);
		return;
	}

	// Function : To swap K th nodes from end and start
	void swapK(int K)
	{
		swap_Kth(&head, & last,N, K);
	}

	// Function : To segregrate even and odd nodes in a list
	void evod()
	{
		segregate(&head,&last);
	}


	// Function : To check for a loop and remove it
	void detectAndRemoveLoop()
	{
		loopCheck(head);
	}
		


};

int main()
{
	LinkedList ll;
	int N, val;
	cout << "Enter the no of elements to be inserted in the list: " ;
	cin >> N;

	for(int i = 0; i < N; i++)
	{
		cin >> val;
		ll.pushEnd(val);
	}

	nLine;
	ll.print();
	nLine;
	int K;
	cin >> K;
	ll.revK(K);	
	
	ll.print();
	return 0;
}
	
