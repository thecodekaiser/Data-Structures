/** 
 * This code implements a circular linked list.
 * In this impelementation, the insertion always takes place at the tail.
 * 
 * Author: thecodekaiser
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Defining a node structure
struct Node
{
	int Key;
	Node * Next;
};

// Defining a circular linked list class
class CircularLL
{

private:
	// Declaring the private global variables
	Node * head, * tail;				// Head and tail of the list
	int N;						// No of elements in the list

	// Function : To print a list starting at a given node
	void printAtNode(Node * h)
	{
		// We have to print till we reach the tail which points to the head
		Node * curr = h;
		while(true)
		{
			if(curr -> Next == head)
			{
				cout << curr -> Key << endl;
				curr = curr -> Next;
				break;
			}
			else
			{
				cout << curr -> Key << " ";
				curr = curr -> Next;
			}
		}

		return;
	}

	// Function : To insert in the linked list at the tail
	void insert(Node ** first, Node ** last, int Data)
	{
		Node * temp  = (Node *) malloc (sizeof(Node));
		temp -> Key  = Data;
		temp -> Next = NULL;

		// If list is empty
		if(isEmpty())
		{
			(*first) = (*last) = temp;
			(*last) -> Next = (*first);
		}
		else
		{
			(*last) -> Next = temp;
			(*last) = temp;
			(*last) -> Next = (*first);
		}

		N++;
	}


public:
	// Constructor
	CircularLL()
	{
		head = tail = NULL;
		N    = 0;
	}

	// Function : To check if the list is empty
	bool isEmpty()
	{
		return N == 0;
	}

	// Function : To get the length of list
	int count()
	{
		return N;
	}

	// Function : To insert some new data in the key
	void insert(int Data)
	{
		insert(&head, &tail,Data);
	}

	// Function : To print the list	(from head to tail)
	void printList()
	{
		printAtNode(head);
	}
};

int main()
{
	CircularLL list;
	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.printList();
	return 0;
}	
