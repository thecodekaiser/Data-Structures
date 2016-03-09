/** 
*  Red-Black Trees allow us to finely implement 2-3 trees with very less
*  complications and help in very fast operations.These in turn help us in implementing symbol-tables with very good performance.
*  They gaurrantee a lg N performance for all operations.
*  Here we are implementing left-leaning RBT or LLRB.
*  The good part of this implementation is that it uses all the code that I 
*  used in the implementation of regular BST but with few additional utitilty functions.
*  The core part of the implementation are rotations.
*  Rotations help in maintaining the invariant satisfied.
*  I have learnt this implementation from Sedgewick's implementation in the book Algorithms by Sedgewick and Wayne.
*  I am implementing a generic type code for the first time so it might have a little mistake. :)
   
   Author : thecodekaiser
*/

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<queue>
#include<stack>
#include<vector>
#include<cstring>

using namespace std;

#define it(i,N)			for(int i = 0; i < N; i++)
#define FOR(i,a,N)		for(int i = a; i <= N; i++)
#define FORR(i,a,N)		for(int i = N; i >= a; i--)

static int RED   = 1;
static int BLACK = 0;

// Defining a node
template <typename T>
struct Node 
{
	T Key;
	size_t Value;
	int Colour;
	long SZ;

	// Child links
	Node<T> * LEFT, * RIGHT;

	// Constructor
	Node<T>(T K, size_t V, int C, long sz)
	{
		Key = K, Value = V, Colour = C, SZ = sz;
		LEFT = RIGHT = NULL;
	}

};

class TreeEmptyException
{
public:
	TreeEmptyException()
	{
		cout <<"The tree is empty." << '\n';
	}
};


// Now here I am defining the RED-BLACK Tree data-sructure
template <class A_Type>  class LLRB
{
	// This is the root of the tree
public:
	Node <A_Type> * root;

	// Our constructor
	LLRB <A_Type> ()
	{
		root = NULL;
	}
private: 
	// Function: To clear the tree recursively
	void clearTree(Node <A_Type> * x)
	{
		if (x == NULL)				return;
		if (x -> LEFT != NULL)		clearTree (x -> LEFT);
		if (x -> RIGHT != NULL)		clearTree (x -> RIGHT);
		free(x);
		return;
	}

	// Function: To give the count of the nodes rooted at given node
	long size(Node <A_Type> * h)
	{
		if (h == NULL)		return 0;
		else			return h -> SZ;
	}

public:
	// Function: To destroy the tree recursively
	// Destructor
	~LLRB <A_Type> ()
	{
		clearTree(root);
	}

	// Function : To check if the tree is empty
	int isEmpty()
	{
		return (root == NULL);
	}

	/************************************************
	*	PRIVATE HELPER METHODS USED IN	 	*
	*		INSERTION AND DELETION		*
	*	(Basically rotations and moving)	*
	*************************************************/

private:

	// Function : To check whether a given node is RED or NOT
	int isRed(Node <A_Type> * h)
	{
		if	(h == NULL)		return BLACK;			// NULL LINKS ARE BLACK
		else				return (h -> Colour == RED);	// Check if the colour is red or not
	}

	// Function : To help in the left rotation of the link
	// Note	    : We basically use this when we have a right leaning red-link
	Node <A_Type> *  rotateLeft(Node <A_Type> * h)
	{
		Node <A_Type> * x   =		h -> RIGHT;
		h -> RIGHT	    =		x -> LEFT;
		x -> LEFT	    =		h;
		x -> Colour	    =		x -> LEFT -> Colour;
		x -> LEFT -> Colour =		RED;
		x -> SZ		    =		h -> SZ;
		h -> SZ	   	    =		size (h -> RIGHT) + size(h -> LEFT) + 1;

		return x;
	}

	// Function : To help in the right rotation of the link
	// Note		: We basically use this when we want a temporary right-leaning red link
	Node <A_Type> *  rotateRight(Node <A_Type> * h)
	{
		Node <A_Type> * x   =		h -> LEFT;
		h -> LEFT	    =		x -> RIGHT;
		x -> RIGHT	    =		h;
		x -> Colour	    =		x -> RIGHT -> Colour;
		x -> RIGHT -> Colour =		RED;
		x -> SZ		    =		h -> SZ;
		h -> SZ		    =		size (h -> RIGHT) + size(h -> LEFT)	+ 1;

		return x;
	}

	// Function : To help in flipping the colour of the parent link and its children
	// Note		: Basically done when both the child nodes have different coloured links than the parent node
	void flipColours(Node <A_Type> * h)
	{
		h -> Colour	      =       ! h -> Colour;
		h -> LEFT  -> Colour  =       ! h -> LEFT  -> Colour;
		h -> RIGHT -> Colour  =       ! h -> RIGHT -> Colour;
	}

	// Function : To move a red-link right-wards temporarily
	// Note	    : Used when we go down in the delete procedure to maintain the invariant temporaliy
	//	      Assuming that h is red and both h.right and h.right.left are black,
	//            make h.right or one of its children red
	Node <A_Type> * moveRedRight(Node <A_Type> * h)
	{
		flipColours(h);
		if (isRed (h -> LEFT -> LEFT) )
		{
			h = rotateRight(h);
		}
		return h;
	}

	// Function : To move a red-link left-wards temporarily
	// Note	    : Used when we go down in the delete procedure to maintain the invariant temporaliy
	//    	      Assuming that h is red and both h.left and h.left.left are black,
	//            make h.left or one of its children red
	Node <A_Type> * moveRedLeft(Node <A_Type> * h)
	{
		flipColours(h);
		if (isRed (h -> RIGHT -> LEFT) )
		{
			h -> RIGHT = rotateRight(h -> RIGHT);
			h          = rotateLeft (h);
		}
		return h;
	}

	// Fucntion : To balance the tree as we go up a tree recursively and restore the tree invariant
	// Note	    : Tree Invariants:	1.] No two red-links can be joined to one node
	//				2.] We can't have a right leaning red node but only left-leaning red-links
	Node <A_Type> * balance(Node <A_Type> * h)
	{
		if (isRed(h -> RIGHT))					h = rotateLeft(h);
		if (isRed(h -> LEFT) && isRed(h -> LEFT -> LEFT))	h = rotateRight(h);
		if (isRed(h -> LEFT) && isRed(h -> RIGHT))		flipColours(h);

		h -> SZ = size(h -> LEFT) + size(h -> RIGHT) + 1;
		
		return h;
	}

	/*********** HELPER FUNCTIONS' DEFITIONS ENDS HERE ************/


	/************************************************
	*		STANDARD BST-SEARCH		*
	*************************************************/

private:
	// Function : To iterate over all nodes and return the value for a given key
	size_t gt(Node <A_Type> * h, A_Type K)
	{	
		while (h != NULL)
		{
			if       (h -> Key < K)		h = h -> RIGHT;
			else if  (h -> Key > K)		h = h -> LEFT;
			else				return h -> Value;
		}
		return NULL;
	}

public:
	// Function : To return the value related to a given key in the tree
	size_t GET(A_Type K)
	{
		return (gt(root, K));
	}

private:
	// Function : To check if a given key is rooted at a given node
	int cntains(Node <A_Type> * h, A_Type K)
	{
		return (gt(root, K) != NULL);
	}

public:
	// Function : To check if a given key exists in the tree
	int CONTAINS(A_Type K)
	{
		return (GET(K) != NULL);
	}

	/*********** SEARCH FUNCTIONS END HERE ************/
	


	/************************************************
	*         RED-BLACK UTILITY FUNCTIONS		*
	*************************************************/

private:
	// Function : To give the height of the sub-tree rooted at a given node
	long hgt(Node <A_Type> * h)
	{
		if (h == NULL)	return -1;
		else
			return 2 + max(hgt(h -> LEFT), hgt(h -> RIGHT));
	}

public:
	// Function : To give the heiht of the tree
	long HEIGHT()
	{
		return hgt(root);
	}

	/*********** UTILITY FUNCTIONS END HERE ************/
	

	/************************************************
	*	ORDERED SYMBOL TABLE FUNCTIONS		*
	*************************************************/
	
private:
	// Function : To give a node with the minimum key value rooted at a particular node
	Node <A_Type> * mn(Node <A_Type> * h)
	{
		if	(h ->LEFT == NULL)	return h;
		else				return mn(h -> LEFT);
	}

public:
	// Function : To give the min key in the tree
	A_Type MIN()
	{
		Node <A_Type> * x = mn(root);
		if(x == NULL)		return NULL;
		else			return x -> Key;
	}

private:
	// Function : To give a node with the maximum key value rooted at a particular node
	Node <A_Type> * mx(Node <A_Type> * h)
	{
		if	(h -> RIGHT == NULL)	return h;
		else				return mx(h -> RIGHT);
	}

public:
	// Function : To give the max key in the tree
	A_Type MAX()
	{
		Node <A_Type> * x = mx(root);
		if(x == NULL)		return NULL;
		else			return x -> Key;
	}

private:
	// Function: To give the floor of a key rooted at a given node
	Node <A_Type> * flr(Node <A_Type> * x, A_Type K)
	{
		if (x == NULL)
			return NULL;
		else if (x->key == K)
			return x;
		else if	(K < x->key)			// Look for floor in the left-subtree
			return flr(x->left,K);

		Node <A_Type> * t = flr(x->right,K);	// Search for floor in right-subtree only 
							// if a value smaller than given key exists there
		if (t != NULL)	return t;
		else return x;
	}

public:
	// Function : To give the floor of a key in the tree
	A_Type FLOOR(A_Type K)
	{
		Node <A_Type> * h = flr(root, K);
		if(h == NULL)		return NULL;
		else			return h -> Key;
	}

private:
	// Function: To give the ceil of a key rooted at a given node
	Node <A_Type> * cl(Node <A_Type> * x, A_Type K)
	{
		if (x == NULL)
			return NULL;
		else if (x->key == K)
			return x;
		else if	(K > x->key)		// Look for ceil in the right-subtree
			return cl(x->right, K);

		Node <A_Type> * t = cl(x->left, K);	// Search for floor in left-subtree only 
							// if a value greater than given key exists there
		if (t != NULL)			return t;
		else return x;
	}

public:
	// Function : To give the floor of a key in the tree
	A_Type CEIL(A_Type K)
	{
		Node <A_Type> * h = cl(root, K);
		if(h == NULL)		return NULL;
		else			return h -> Key;
	}

private:
	// Function: To give the rank of the key rooted at a given node
	// Rank gives us no of keys which are smaller than the present key
	long rnk(Node <A_Type> * x, A_Type Key)
	{
		if (x == NULL)			return 0;
		else if (Key < x->Key)		return rnk(x->LEFT,Key); 	 // If the key is in the left sub-tree
		else if	(Key > x->Key)		return 1 + size(x->LEFT) + rnk(x->RIGHT,Key);	// If the key is in the right sub-tree
		else				return size(x->LEFT);		// If the key has been found
	}

public:
	// Function : To give the rank of the key in the tree
	long RANK(A_Type K)
	{
		return rnk(root, K);
	}

private:
	// Function: To print one node
	void printOne(Node <A_Type> * T)
	{
		cout<<T->Key<<"\t\t"<<T->Value<<"\t\t"<<RANK(T -> Key)<<endl;
	}

private:
	// Function to print the whole tree  in inorder traversal
	void printAll(Node <A_Type> * x)
	{
		if(x != NULL)
		{
			printAll(x->LEFT);
			printOne(x);
			printAll(x->RIGHT);
		}
		return;
	}

public:
	// Function to print the whole tree
	void printAll()
	{
		cout<<"KEY"<<"\t\t"<<"VALUE"<<"\t\t"<<"RANK"<<endl;
		printAll(root);
		return;
	}

private:
	// Function : To give the in order traversal of the tree from any given node
	void in_order(Node <A_Type> * x, queue<A_Type> & Q)
	{
		if (x == NULL) return ;
		in_order(x->left,Q);
		Q.push(x->key);
		in_order(x->right,Q);
		return;
	}

public:
	// Function : To give the in-order traversal of the tree from the root
	void TRAVERSE(queue<A_Type> & Q)
	{
		in_order(root, Q);
		return;
	}

	/*********** ORDERED OPERATIONS END HERE ************/


	/************************************************
	*	     RED-BLACK INSERTION		*
	*************************************************/

private:

	// Function : To insert a key value-pair otherwise overwrite the new value if the key is already present
	Node <A_Type> * inst (Node <A_Type> * h, A_Type K, size_t V)
	{
		// If adding a new link then return a new red node of size 1
		if (h == NULL)
		{
			return new Node <A_Type>(K, V, RED, 1);
		}

		if (h -> Key < K)      h -> RIGHT = inst (h -> RIGHT, K, V);  // If given key is greater than key at present node go right
		else if (h -> Key > K) h -> LEFT = inst (h -> LEFT, K, V);    // If given key is smaller than key at present node go left
		else	               h -> Value = V;			      // Else update value

		// Now balance the tree

		if (isRed(h -> RIGHT)&& !isRed(h -> LEFT))		h = rotateLeft(h);
		if (isRed(h -> LEFT) && isRed(h -> LEFT -> LEFT))	h = rotateRight(h);
		if (isRed(h -> LEFT) && isRed(h -> RIGHT))		flipColours(h);

		h -> SZ = size(h -> LEFT)  + size(h -> RIGHT) +	1;

		return h;
	}

public:
	// Function : To insert a key-value pair in the tree rooted at the ROOT
	void INSERT(A_Type K, size_t V)
	{
		root = inst(root, K, V);
		root -> Colour = BLACK;
	}

	/*********** INSERTION FUNCTIONS END HERE ************/


	/************************************************
	*	     RED-BLACK DELETION			*
	*************************************************/

	// 1.] First in series is the Delete Minimum function

private:
	// Function : To remove the minimum from the tree and also maintain deletion invaraint
	// Note	    : We must understand that when we travel in the left sub-tree we must have each node red
	//	      or its left child red so that it helps us in maintaining invariant when we delete it
	//	      We fix all variants when we go up recursively
	Node <A_Type> * dMn(Node <A_Type> * h)
	{
		if (h -> LEFT == NULL)
			return NULL;

		if (!isRed(h -> LEFT) && !isRed(h -> LEFT -> LEFT))
			h = moveRedLeft(h);

		h -> LEFT = dMn(h -> LEFT);

		return balance(h);
	}

public:
	// Function : To delete the minimum from the tree
	void delMIN()
	{
		if (isEmpty())	throw TreeEmptyException();

		// If both children of root are black then set it to RED
		if (!isRed(root -> LEFT) && !isRed(root -> RIGHT))
			root -> Colour = RED;

		root = dMn(root);
		if (!isEmpty())  root -> Colour = BLACK;
	}

	// 2.] Second in series is the Delete Maximum function

private:
	// Function : To remove the maximum from the tree and also maintain deletion invaraint
	// Note	    : We must understand that when we travel in the right sub-tree we must have each node red
	//	      or its left child red so that it helps us in maintaining invariant when we delete it
	//            We fix all variants when we go up recursively
	Node <A_Type> * dMx(Node <A_Type> * h)
	{
		if (isRed(h -> LEFT))
			h = rotateRight(h);

		if (h -> RIGHT == NULL)
			return NULL;

		if (!isRed(h -> RIGHT) && !isRed(h -> RIGHT -> LEFT))
			h = moveRedRight(h);

		h -> RIGHT = dMx(h -> RIGHT);

		return balance(h);
	}

public:
	// Function : To delete the minimum from the tree
	void delMAX()
	{
		if (isEmpty())	throw TreeEmptyException();

		// If both children of root are black then set it to RED
		if (!isRed(root -> LEFT) && !isRed(root -> RIGHT))
			root -> Colour = RED;

		root = dMx(root);
		if (!isEmpty())  root -> Colour = BLACK;
	}

	// 3.] Finally we have the delete functions 

private:
	// Function : To delete a given key-value pair from the tree
	Node <A_Type> * del(Node <A_Type> * h, A_Type K)
	{
		// If searching in the left sub-tree
		if (h -> Key > K)
		{
			if (!isRed(h -> LEFT) && !isRed(h -> LEFT -> LEFT))
				h = moveRedLeft(h);

			h -> LEFT = del(h -> LEFT, K);
		}
		else {
			
			if (isRed(h -> LEFT))
				h = rotateRight(h);

			if(h -> Key == K && h -> RIGHT == NULL)
				return NULL;

			if(!isRed(h -> RIGHT) && !isRed(h -> RIGHT -> LEFT))
				h = moveRedRight(h);

			if(h -> Key == K)
			{
				Node <A_Type> * x =   mn(h -> RIGHT);
				h -> Key	  =   x -> Key;
				h -> Value	  =   x -> Value;

				h -> RIGHT	  =   dMn(h -> RIGHT);	// We are just using Hibbard Deletion but also 
									// maintaining the tree invariants
			}

			else
				h -> RIGHT = del(h -> RIGHT, K);
		}
		return balance(h);
	}

public:
	// Function : To delete a given key from the tree
	void DELETE(A_Type K)
	{
		if (!CONTAINS(K))
		{
			cout<<"SYMBOL TABLE DOESN'T CONTAIN THE KEY: "<<K<<endl;
			return;
		}

		// If both children of root are black then set it to RED
		if (!isRed(root -> LEFT) && !isRed(root -> RIGHT))
			root -> Colour = RED;

		root = del(root, K);
		if (!isEmpty())  root -> Colour = BLACK;
	}

	/*********** DELETION FUNCTIONS END HERE ************/
	

	/************************************************
	*	    RED-BLACK CONSISTENCY		*
	*************************************************/
private:
	// Function : To check if the every path from the root to leaf has given number of black links
	int isBalanced(Node <A_Type> * h, int Black)
	{
		if (h == NULL)		return	(Black == 0);
		if (!isRed(h))		Black--;
		return isBalanced(h -> LEFT, Black) &&	isBalanced(h -> RIGHT, Black);
	}

public: 
	// Function: To check if every path from the root has the same number of the black links
	int isBalanced()
	{
		int Black = 0;			// Number of black links from root to the min
		Node <A_Type> * h = root;
		while (h != NULL)
		{
			if (!isRed(h))	
				Black++;
			h = h -> LEFT;
		}
		return	isBalanced(root, Black);
	}

private:
	// Function : To check if the given tree is compliant with the tree invariants completely
	int is23(Node <A_Type> * h)
	{
		if (h == NULL)		return 1;
		if (isRed(h -> RIGHT))	return 0;
		else if(h != root && isRed(h -> LEFT)  &&   isRed(h -> LEFT -> LEFT))	return 0;
		return is23(h -> LEFT) && is23(h -> RIGHT);
	}

public:
	// Function : To chek if the tree is 2-3 tree
	int is23()
	{
		return is23(root);
	}

	/*********** CONSISTENCY FUNCTIONS END HERE ************/

	
	/************************************************
	*	    RANGE SEARCH AND COUNT		*
	*************************************************/

	//... TO BE ADDED SOON WHEN I GET IT CLEARY :>

};


int main()
{
	LLRB <char> RBT;

	char str[50];

	scanf("%s",str);
	string ss = str;
	//cout<<ss<<endl;

	for(int i = 0; i < ss.length(); i++)
	{
		char ch = ss[i];
		RBT.INSERT(ch,i);
	}

	RBT.printAll();

	cout<<"LARGEST KEY: "<<RBT.MAX()<<"\t SMALLEST KEY: "<<RBT.MIN()<<endl;

	return 0;
}
		
