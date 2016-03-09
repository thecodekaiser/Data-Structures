/**
 * A typical deque implementation support the following operations.
 * Insert at front an element,
 * insert at back an element,
 * remove from back an element, 
 * remove from front an element, 
 * list the front element and list the back element.
 * It can be implemented using a doubly linked list
 * Author : thecodekaiser
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class DequeEmptyException
{
public:
	DequeEmptyException()
	{
		cout<<" Deque Empty "<<endl;
	}
};

class Node
{
public:
	int data;
	Node *prev;
	Node *next;
};

class Deque{
private:
	Node* front;
	Node* rear;
	int count;
public:
	//This is a constructor
	Deque(){
		front = NULL;
		rear = NULL;
		count =0;
	}
	//Method to insert at front
	void insertFront(int element){
		//First create a new node
		Node* temp =new Node();
		temp->data = element;
		temp->next = NULL;
		temp->prev = NULL;

		if(count==0){
			//Add the first element
			front = rear = temp;
		}
		else{
			//Prepend to the links and fix links
			temp->next = front;
			front->prev = temp;
			front = temp;
		}
		count+=1;
	}

	int removeFront(){
		//Check if the deque is already empty
		if(count==0){
			throw DequeEmptyException();
		}
		//Data in the front node
		int data = front->data;

		//Delete the front node and fix the links
		Node* temp =front;
		if(front->next!=NULL){
			front = front->next;
			front->prev = NULL;
		}
		else
			front = NULL;
		count-=1;
		delete temp;
		return data;
	}

	void insertBack(int element){
		//Create a new node
		Node* temp =new Node();
		temp->data = element;
		temp->next = NULL;
		temp->prev = NULL;

		//If empty add the new element
		if(count==0){
			front = rear = temp;
		}
		else {
            // Append to the list and fix links
            rear->next = temp;
            temp->prev = rear;
            rear = temp;
        }

        count++;
    }

    int removeBack()
    {   
		//Check if already empty
        if ( count==0 ) {
            throw new DequeEmptyException();
        }

        //  Data in the rear node
        int data = rear->data;

        // Delete the front node and fix the links
        Node* temp = rear;
        if ( rear->prev != NULL )
        {
            rear = rear->prev;
            rear->next = NULL;
        }
        else
        {
            rear = NULL;
        }
        count--;
        delete temp;

        return data;
    }
  
    int Front()
    {          
        if ( isEmpty() )
            throw new DequeEmptyException();

        return front->data;
    }

    int Back()
    {
        if ( isEmpty() )
            throw new DequeEmptyException();

        return rear->data;
    }
  
    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }
};


int main()
{      
    // Stack behavior using a general dequeue
    Deque q;
    try {
        if ( q.isEmpty() )
        {
            cout << "Deque is empty" << endl;
        }

        // Push elements
        q.insertBack(100);
        q.insertBack(200);
        q.insertBack(300);

        // Size of queue
        cout << "Size of dequeue = " << q.size() << endl;

        // Pop elements
        cout << q.removeBack() << endl;
        cout << q.removeBack() << endl;
        cout << q.removeBack() << endl;
    }
    catch (...) {
        cout << "Some exception occured" << endl;
    }

    // Queue behavior using a general dequeue
    Deque q1;
    try {
        if ( q1.isEmpty() )
        {
            cout << "Deque is empty" << endl;
        }

        // Push elements
        q1.insertBack(100);
        q1.insertBack(200);
        q1.insertBack(300);

        // Size of queue
        cout << "Size of dequeue = " << q1.size() << endl;

        // Pop elements
        cout << q1.removeFront() << endl;
        cout << q1.removeFront() << endl;
        cout << q1.removeFront() << endl;
    }
    catch (...) {
        cout << "Some exception occured" << endl;
    }
}
