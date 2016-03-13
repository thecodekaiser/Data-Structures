/* This implementation uses a linked list of nodes that represents an edge.	
   Author : thecodekaiser
   Verdict : AC
   Now I will implement it using AD-lists and UF also :)
*

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

struct Node {
	int T,H;		// Each node has one head and one tail
	Node * next;
};


class LinkedList
{
private:
	// Declaring the ends of the linked list
	Node * front;
	int count;	// To keep the count of elements in the list
	int nodes;

	// Public Constructor
public:
	LinkedList(int N)
	{
		front = NULL;
		count = 0;
		nodes = N;
	}

	// Method to put some data at the beginning of some linked list
	void push(int H, int T)
	{
		// Check if the data is null
		if(H == NULL || T == NULL)
		{
			cout<<" NULL DATA INSSERTION IS NOT ALLOWED "<<endl;
			return;             // Exit 
		}
		// Else create a temp node
		Node * temp = new Node();
		temp->H = H;
		temp->T = T;
		temp->next = NULL;
		// Check that if it is the first element then we have to link first to the last
		if(count == 0)
		{
			front = temp;
		}
		else
		{
			// Fix the links and append it to the list
			temp->next = front;
			front = temp;
		}
		count += 1;		// Increase the count
	}

	int Del(Node * h)
	{
		Node * temp, *prev;
		temp = front;
		while(temp != NULL)
		{
			if(temp == h)
			{
				if(temp == front)
				{	
					front = temp->next;
					free(temp);
					count -= 1;
					return 1;				// 1-> denotes success
				}
				else
				{
					prev->next = temp->next;
					free(temp);
					count -= 1;				
					return 1;
				}
			}
			else
			{
				prev = temp;
				temp = temp ->next;
			}
		}
		return 0;
	}

	// Method to give the count of elements in the list
	int Count()
	{
		return count;
	}	

	// Method to print the whole list in front to end order
	void print()
	{
		Node * temp = front;
		while(temp != NULL)
		{
			cout<<"("<<temp->H<<", "<<temp->T<<")"<<endl;
			temp = temp->next;
		}
		cout<<"COUNT: "<<count<<endl;
	}

	
	// Contract sub-routine : Only need to remove one edge that connects the two nodes 
	// and also any self-loops and make changes by exchanging (H,x) with (T,x) and (x,H) with (x,T) for given (H,T)
	void make_changes(int H, int T)
	{
		Node * h, * p;
		h = p = front;
		int code = 0;

		//cout << H << "," << T << endl;
		while(h != NULL)
		{
			// Checking if we have found the given node and also that we are deleting only this edge and no other
			if ((h->H == H && h->T == T) && code == 0)
			{
				//cout << "F" << endl;
				// Check if this is the end of the list
				if(h -> next == NULL)
				{
					// Delete this edge and return 
					{	Del(h);		return;		}
				}
				else
				{
					// Delete this edge and again set temp = p -> next
					p = h->next;
					Del(h);	code = 1;
					h = p;
					continue;
				}
			}

			// Replace (H,y) with (T,y)
			if (h -> H == H)	h -> H = T;

			// Replace (x,H) with (x,T)
			if (h -> T == H)	h -> T = T;

			// Tackle self loops
			if(h -> H == h -> T )
			{
				//cout << "FOUND IT" << endl;
				// Check if this is the end of the list
				if(h -> next == NULL)
				{
					// Delete this edge and return 
					{	Del(h);		return;		}
				}
				else
				{
					// Delete this edge and again set temp = p -> next
					p = h->next;
					Del(h);	code = 1;
					h = p;
					continue;
				}
			}

			h = h -> next;
			p = h;
		}
	}

	void prt(int x)
	{
		int i = 1;
		Node * h = front;
		while(i <= x-1)
			h = h -> next, i++;

		cout << h -> H << "," << h -> T << endl;
		return ;
	}

	// Returns the number of crossing found in the present cuts
	// Randomly selects an edge and performs the make_changes function according the value of H and T for that edge
	int solve_problem()
	{
		Node * h;
		//cout << nodes << endl;
		int r,i;
		while(nodes > 2)
		{
			r = rand() % count + 1;
			//cout << r << endl;
			
			i = 1;
			h = front;
			while(i <= r-1)
				h = h->next, i+=1;
			//cout << h->H << "," << h -> T << endl;
			
			make_changes(h->H , h->T);
			
			nodes -= 1;
		}

		return count;
	}


};

	void buildGraph(LinkedList & l) {
		  ifstream File_Reader("kargerMinCut.txt");
		  
		  int ** ptr = (int **)malloc(201*sizeof(int*));
		  for(int i =0;i<201;i++)	ptr[i] = (int *)calloc(201,sizeof(int));

		  string line;
		  int x = 0;
		  int y = 0;
		  int edgeIndex = 0;

		  while (getline(File_Reader, line)) { //Reads the file line by line
			istringstream iss(line);
			iss >> x;  //Assigns the first 'word' (integer) to x


			while (iss >> y) {  //Loops through the rest of the line, assigning each 'word' (integer) to y one at a time
				if(ptr[x][y] == 0 && ptr[y][x] == 0)
				{
					l.push(x,y);
					ptr[x][y] = 1;
				}
			}
		  }
	}



		

int main()
{
	srand(time(NULL));
	
//	ll.print();

//	ll.make_changes(1,1);
//	ll.make_changes(1,2);
//	ll.make_changes(7,8);
	int min = 200 * 200;
	for(int i = 0; i < 100; i++)
	{
		LinkedList ll(200);
		buildGraph(ll);
		int d = ll.solve_problem();
		//cout << d << endl;
		if(min > d)
			min = d;
	}
	cout << min << endl;
	return 0;
}
*/