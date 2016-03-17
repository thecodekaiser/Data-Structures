/* Here we are implementing a simple BST.
   A BST is simply a reference to a root node.
   A node is comprised of five fields.
	.) A key, a value and a count associated with it
	.) A reference to left and right child nodes
   This implementation has all the ordered operations 
   of a BST implemented in a fine manner.

*/
#include <bits/stdc++.h>

using namespace std;

#define it(i,N)			for(int i = 0; i < N; i++)
#define FOR(i,a,N)		for(int i = a; i <= N; i++)
#define FORR(i,a,N)		for(int i = N; i >= a; i--)

typedef long long ll;
typedef long l;

// Defining the node
struct Node
{
	// Declaring the variables
	ll key;
	ll value;
	ll count;                         // To keep an acccount of the nodes rooted at that particular node

	// And a reference to child nodes
	Node * left, * right;

	// Constructor
	Node(ll Key,ll Value, ll Count)
	{
		key = Key,value = Value, count = Count;
		left = right = NULL;
	}
};


// Now we will implement the binary search tree
class BST
{
private:	
	// Let us decalre the pointer to the root node
	Node * root;

private:
	// Prinvate implementor function to get the size of the sub-tree rooted at that particular node
	ll size(Node * x)
	{
		if (x == NULL)	return 0;
		return		x->count;
	}

	// Mehtod to clear the tree
	// Recursively traverse the tree and destroy all nodes
	void clearTree(Node * root)
	{
		if(root == NULL)		return;					// IF it is null do nothing
		if(root->left != NULL)		clearTree(root->left);			// Clear the left sub-tree
		if(root->right != NULL)		clearTree(root->right);			// Clear the right sub-tree
		delete root;
		return ;
	}

	// Method to duplicate a node in the tree
	// This is used to return a complete structure
	// without having to give the access into the tree using pointers
	Node * dup_Node(Node * x)
	{
		Node * dup;
		dup = new Node(x->key,x->value,x->count);
		*dup = *x;         // Copy the data-structure
		dup->left = NULL;
		dup->right = NULL; // Set the pointers to NULL
		return dup;
	}

	// Method to insert a node in the tree
	// Testing: Prints 1 if successful insertion is done 
	Node * insert(Node * T,ll Key,ll Value)
	{
		if(T == NULL)	// If no node is present at the current position then insert a node at this position
		{
			return new Node(Key,Value,1);

		}
		else if(T->key < Key)
			T->right = insert(T->right, Key, Value); // If the Key is bigger insert at the right subtree and return the pointer
		else if(T->key > Key)
			T->left = insert(T->left, Key, Value);	// If the Key is smaller insert at the left subtree and return the pointer


		T->count = 1 + size(T->left) + size(T->right);

		return T;    					// Return the pointer
	}

	// Private method to print one node
	void printOne(Node * T)
	{
		cout<<T->key<<"\t\t"<<T->value<<endl;
	}

	// Function to print the whole tree
	void printAll(Node * x)
	{
		if(x != NULL)
		{
			printAll(x->left);
			printOne(x);
			printAll(x->right);
		}
		return;
	}

	// Private function to give the floor of a key
	Node * floor(Node * x, ll Key)
	{
		if (x == NULL)
				return NULL;
		else if (x->key == Key)
				return x;
		else if	(Key < x->key)
				return floor(x->left,Key);
		
		Node * t = floor(x->right,Key);
		if (t != NULL)		return t;
		else return x;
	}

	// Private Function to give the ceiling of a key
	Node * ceil(Node * x, ll Key)
	{
		if(x == NULL)
			return NULL;
		else if (x->key == Key)
			return x;
		else if (Key > x->key)
			return ceil(x->right, Key);
		
		Node * t = ceil(x->left, Key);
		if (t != NULL)			return t;
		else					return x;
	}

	// Implementor function for the rank method 
	// Rank gives us no of keys which are smaller than the present key
	ll rank(Node * x, ll Key)
	{
		if (x == NULL)			return 0;
		else if (Key < x->key)		return rank(x->left,Key);	// If the key is in the left sub-tree
		else if	(Key > x->key)		return 1 + size(x->left) + rank(x->right,Key);	// If the key is in the right sub-tree
		else				return size(x->left);		// If the key has been found
	}

	// Implementor function to help in the in order traversal of the tree
	void in_order(Node * x, queue<ll> & Q)
	{
		if (x == NULL) return ;
		in_order(x->left,Q);
		Q.push(x->key);
		in_order(x->right,Q);
	}


	// Implementor function to delete the minimum key in a tree
	Node * deleteMin(Node * T)
	{
		if (T->left == NULL)		return T->right;
		T->left = deleteMin(T->left);
		T->count = 1 + size(T->left) + size(T->right);
		return T;
	}

	// Implementor function to delete the maximum key in a tree
	Node * deleteMax(Node * T)
	{
		if (T->right == NULL)	return T->left;
		T->right = deleteMax(T->right);
		T->count = 1 + size(T->left) + size(T->right);
		return T;
	}

	// Implementor Method to find the smallest in the tree
	Node * min(Node * T)
	{
		Node * x = T;
		while(x->left != NULL)
		{
			x = x->left;
		}
		if(x->value != NULL)
			return x;
		else
		{
			return NULL;
		}
	}

	// Implementor Method to find the biggest in the tree
	Node * max(Node * T)
	{
		Node * x = root;
		while(x->right != NULL)
		{
			x = x->right;
		}
		if(x->value != NULL)
			return x;
		else 
		{
			return NULL;
		}
	}

public:
	// Class Constructor 
	BST()
	{
		root = NULL;
		return;
	}

	// Class destructor
	~BST()
	{
		clearTree(root);
		return;
	}

	// Method to check if the tree is empty
	bool isEmpty()
	{
		return (root == NULL);
	}

	// Mehtod to search the tree using an iterative approach
	// Returns the value or NULL if the key is not found 
	ll Search(ll Key)
	{
		Node * x = root;
		while(x != NULL)
		{
			if (Key < x->key)		x = x->left;
			else if (Key > x->key)		x = x->right;
			else
				return x->value;
		}
		return NULL;
	}

	// Function to insert in the tree
	void insert(ll Key,ll Value)
	{
		root = insert(root, Key, Value);      // Returns a pointer to the original root
		//cout<<"Successful"<<endl;
		return;
	}

	// Method to print the tree given the root node
	void printTree()
	{
		Node * temp = root;
		printAll(temp);                  // Does the actual work
	}

	// Function to return the largest key
	ll max()
	{
		Node * x = max(root);
		return x->key;
	}

	// Function to return the smallest key
	ll min()
	{
		Node * x = min(root);
		return x->key;
	}

	// Method to give the floor of the key
	// Returns the largest integer smaller than or equal to the key
	ll floor(ll Key)
	{
		Node * x = floor(root,Key);
		if (x == NULL) return NULL;

		return x->key;
	}

	// Function to give the ceiling of any key
	// Returns the smallest integer greater than or equal to the key
	ll ceil(ll Key)
	{
		Node * x = ceil(root,Key);
		if (x == NULL) return NULL;

		return x->key;
	}

	// Function to get the size of the tree
	ll size()
	{
		return size(root);
	}

	// Function to give the rank of a particular node
	// Rank gives us the no of keys smaller than the key at the current node
	ll rank(ll key)
	{
		return rank(root,key);
	}

	// Function to do in-order traversal of the tree
	void traverse(queue<ll>  & Q)
	{
		in_order(root,Q);
	}

	// Function to delete the minimum key tree
	void delMin()
	{
		root = deleteMin(root);
	}

	// Function to delete the maximum key in the tree
	void delMax()
	{
		root = deleteMax(root);
	}

private:
	// Finally we have the implementor function for deletion operation
	// It has 3 cases:
	// 1. The node has no child   -> Simply return left
	// 2. The node has 1 child    -> Return the pointer to that child
	// 3. The node has 2 children -> Set the minimum in the right sub-tree as the root of left and right sub-trees at that node
	// This mehtod is know as the HIBARD METHOD
	Node * delT(Node * T, ll Key)
	{
		if (T == NULL)	        return NULL;			// The node has no child
		else if (Key < T->key)  T->left  = delT(T->left,Key);
		else if (Key > T->key)	T->right = delT(T->right,Key);
		else
		{	
			// The tree has one child
			if		(T->left == NULL)		return T->right;
			else if	(T->right == NULL)		return T->left;

			Node * x;
			x = min(T->right);
			x->right = deleteMin(T->right);
			x->left = T->left;
		}
		T->count = 1 + size(T->left) + size(T->right);
		return T;
	}

public:
	// Function to delete any key in the tree
	void Del(ll Key)
	{
		root = delT(root, Key);
	}
};


// Tester function
int main()
{
	BST bT;	
	cout<<"HELLO"<<endl;
	cout<<"This is a sample program on a Binary Search Tree."<<endl;
	cout<<"You can do all operations in lg N time except the deletion operation."<<endl;
	cout<<"You can do many operations like finding the max,min,floor,ceil of a given key etc."<<endl;
	cout<<"NOW, in order to create the list press 1 else press 0 to exit the program."<<endl;
	int CODE;
	scanf("%d",&CODE);
	if(CODE == 0)
		exit(0);
	else
	{
		char cmd[50];
		ll Key, Value;
		cout<<"Now you can do the ordered operations on the tree."<<endl;
		cout<<"1. Press I to insert followed by Key-Value Pair."<<endl;
		cout<<"2. Press D to delete followed by Key."<<endl;
		cout<<"3. Press DMX to delete the largest key."<<endl;
		cout<<"4. Press DMN to delete the smallest key."<<endl;
		cout<<"5. Press FL followed by the Key to display the floor of the key."<<endl;
		cout<<"6. Press CL followed by the Key to display the ceil of the key."<<endl;
		cout<<"7. Press MX to display the largest key."<<endl;
		cout<<"8. Press MN to display the smallest key."<<endl;
		cout<<"9. Press SCH followed by the Key to search  for the key and display its value."<<endl;
		cout<<"10. Press EMP to check if the tree is empty."<<endl;
		cout<<"11. Press RK followed by the key to find the rank of the key in the tree."<<endl;
		cout<<"12. Press SZ to display the size of the tree."<<endl;
		cout<<"13. Press PRT to display the tree in order from left to right."<<endl;
		cout<<"14. Press DONE to end the testing."<<endl;
		
		// Testing starts
		while(true)
		{
			scanf("%s",cmd);
			if(strcmp(cmd,"I") == 0)
			{
				scanf("%lld %lld",&Key,&Value);
				bT.insert(Key,Value);
			}
			else if(strcmp(cmd,"D") == 0)
			{
				scanf("%lld",&Key);
				bT.Del(Key);
			}
			else if(strcmp(cmd,"DMX") == 0)
			{
				bT.delMax();
			}
			else if(strcmp(cmd,"DMN") == 0)
			{
				bT.delMin();
			}
			else if(strcmp(cmd,"MX") == 0)
			{
				cout<<bT.max()<<endl;
			}
			else if(strcmp(cmd,"MN") == 0)
			{
				cout<<bT.min()<<endl;
			}
			else if(strcmp(cmd,"FL") == 0)
			{
				scanf("%lld",&Key);
				cout<<bT.floor(Key)<<endl;
			}
			else if(strcmp(cmd,"CL") == 0)
			{
				scanf("%lld",&Key);
				cout<<bT.ceil(Key)<<endl;
			}
			else if(strcmp(cmd,"SCH") == 0)
			{
				scanf("%lld",&Key);
				Value = bT.Search(Key);
			}
			else if(strcmp(cmd,"EMP") == 0)
			{
				if(bT.isEmpty())
					cout<<"The tree is empty."<<endl;
				else 
					cout<<"The tree is not empty."<<endl;
			}
			else if(strcmp(cmd,"RK") == 0)
			{
				scanf("%lld",&Key);
				cout<<bT.rank(Key)<<endl;
			}
			else if(strcmp(cmd,"SZ") == 0)
			{
				cout<<bT.size()<<endl;
			}
			else if(strcmp(cmd,"PRT") == 0)
			{
				bT.printTree();
			}
			else if(strcmp(cmd,"DONE") == 0)
			{
				exit(0);
			}
			else
			{
				cout<<"Illegal Command.Try again."<<endl;
			}
		}
	}
		return 0;
}

// Tester program ends
