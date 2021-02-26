#include <iostream>
#include <string.h>
#include<fstream>


using namespace std;
class node
  {  
   private: 
     node * right;
     node * left;
	 char *password;
	 char *username;
     //node& operator = ( const node &);
	 friend class tree;
   public:
	 node();
     node( char *, char *);
  };

node:: node()
  {   
   left = NULL;
   right = NULL;
   password = "NULL";
   username = "NULL";
  }
node:: node( char *pswrd, char *usrnm )
  {
   password = pswrd;
   username = usrnm;
   left = NULL;
   right = NULL;

  } 


class tree
  {
   public:     
	 tree();
    // tree( const tree& );
     void emptyTree();
     void addItem( char *, char *);
	 void Insert( node *&, char*, char* );
	 //void DeleteItem();
     bool isEmpty();
	 bool goLeft(node *);
	 bool goRight(node *);
	 bool find( char *, node * );
	 void Destroy( node*& );
	 void PrintTree();
	 void Print( node* );
	 bool verifyUser( char *, char *);
	 void GetPredecessor( node *, char*&);
	 void DeleteNode( node *& );
	 void Delete( node*&, char* );
	 void DeleteItem( char*);
	 void inOrder();
	 void preOrder();
	 void postOrder();
	 void inOrderOut(node* cursor, ofstream& fout);
 	 void preOrderOut(node* cursor, ofstream& fout);
 	 void postOrderOut(node* cursor, ofstream& fout);
	 void inFile();
    // tree& operator = ( const tree &);
     ~tree();
   
   private: 
     node * root;
	 node * cursor;
	

  };

tree:: tree()
{
	 root = NULL;
	 cursor = NULL;
 
}

void tree:: emptyTree()
{
	 if( root != NULL )
	 {
	  Destroy(root);
	  root = cursor = NULL;
	 }
}

void tree:: addItem( char *usrnm, char *pswd )
{
 Insert(cursor, usrnm, pswd );
}

void tree:: Insert( node * & cursor, char * usrnm, char * pswd )
{
	 int val;

	 if(cursor == NULL )
	 {  // base case
		   cursor = new node[2];
		   cursor->right = NULL;
		   cursor->left = NULL;
		   cursor->username = usrnm;
		   cursor->password = pswd;
	 }
	 else
	 {
		  val = strcmp( usrnm, cursor->username );
		  if(val < 0)
		  {
		   Insert(cursor->left, usrnm, pswd );
		  }
		  else
		   Insert(cursor->right, usrnm, pswd );
	 }
}


void tree:: DeleteItem(char * usrnm )
{
	 cursor = root;
	 Delete(root, usrnm);
}

void tree:: Delete(node *& cursor, char * usrnm)
{
	 int val;
	 val = strcmp(cursor->username, usrnm);
	 if(val > 0)
	   Delete(cursor->left, usrnm);
	 else if(val < 0)
	   Delete(cursor->right, usrnm);
	 else
	   DeleteNode(cursor);
} 

void tree:: DeleteNode( node*& cursor )
{
	 char * usrnm;
	 node * tempPtr = new node[2];
	 tempPtr->left = cursor->left;
	 tempPtr->right = cursor->right;
	 tempPtr->username = cursor->username;
	 tempPtr->password = cursor->password;

	 if(cursor->left == NULL)
	 { // right child
	   cursor = cursor->right;
	   delete[] tempPtr;
	 }
	 else if(cursor->right == NULL)
	 { // left child
	   cursor = cursor->left;
	   delete[] tempPtr;
	 }
	 else 
	 {
	   GetPredecessor(cursor->left, usrnm);
	   cursor->username = usrnm;
	   Delete(cursor->left, usrnm);
	 }
} 
void tree:: GetPredecessor( node* cursor, char * & usrnm)
{
	 while(cursor->right != NULL)
	   cursor = cursor->right;
	 usrnm = cursor->username;
} 



bool tree:: isEmpty()
{
	 if( cursor == NULL )
	 {
	  return true;
	 }
	 else
	 {
	  return false;
	 }
}


bool tree:: goLeft( node * temp )
{
	 // check to see if there's a left node
	 if(temp->left == NULL )
	 {
	  return false;
	 }

	 // move left
	 temp = temp->left;
	 return true;
}
bool tree:: goRight( node * temp )
{
	 // check to see if there's a right node
	 if(temp->right == NULL )
	 {
	  return false;
	 }

	 // move right
	 temp = temp->right;
	 return true;
	}

	bool tree:: find( char *usrnm, node * finder )
	{
		 int val = 0;
		 finder = root;
		 if( finder != NULL )
		 {
			  val = strcmp( usrnm, finder->username);
			  while( val != 0 )
			  {
				   if( val < 0 )
				   {
					goLeft( finder );
				   }
				   else if( val > 0 )
				   {
					goRight( finder );
				   }
				   else
				   {
					return true;
			   }
		  }
	 }
	 cout << "Error: Username is not in the database." << endl;
	 return false;
}


void tree::PrintTree()
{
	Print(root);
}

void tree:: Print( node* temp )
{
	 char comma = ',';
	 char space = ' ';
	 if(temp != NULL) 
	 {
	   Print(temp->left);
	   cout << temp->username << comma << space << temp->password;
	   Print(temp->right);
	 }
}


void tree:: Destroy(node * & root)
{
	 if(root != NULL) 
	 {
	   Destroy(root->left);
	   Destroy(root->right);
	   delete root;
	 }

}

void tree:: inOrder()
{
	 cursor = root;
	 ofstream fout;
	 //set the output file
	 char fileName[] = "outputFileIn.txt";
	 //open the file
	 fout.open( fileName );
	 //recursively call the inOrder function
	 inOrderOut( cursor, fout );
	 fout.close();
}

void tree:: postOrder()
{
	 cursor = root;
	 ofstream fout;
	  //set the output file
	 char fileName[] = "outputFilePost.txt";
	  //open the file
	 fout.open( fileName );
	  //recursively call the postOrder function
	 postOrderOut( cursor, fout );
	 fout.close();
}

void tree:: preOrder()
{
	 cursor = root;
	 ofstream fout;
	 // set file name
	 char fileName[] = "outputFilePre.txt";
	 // open the file
	 fout.open( fileName );
	 //recursively call the preOrder function
	 preOrderOut( cursor, fout );
	 fout.close();
}

void tree:: inOrderOut(node* cursor, ofstream& fout)
{
 char space = ' ';
	 if(cursor != NULL) 
	 {
	   inOrderOut(cursor->left, fout);
	   fout << cursor->username << space << cursor->password << endl;
	   inOrderOut(cursor->right, fout);
	 }
}
void tree:: preOrderOut(node* cursor, ofstream& fout)
{
 char space = ' ';
	 if(cursor != NULL) 
	 {
	   fout << cursor->username << space << cursor->password << endl;
	   preOrderOut(cursor->left, fout);
	   preOrderOut(cursor->right, fout);
	 }
}
void tree:: postOrderOut(node* cursor, ofstream& fout)
{
	 char space = ' ';
	 if(cursor != NULL) 
	 {
	   postOrderOut(cursor->left, fout);
	   postOrderOut(cursor->right, fout);
	   fout << cursor->username << space << cursor->password << endl;
	 }
}

	 
void tree:: inFile()
{
	 char * usrnm = new char[20];
	 char * pswd = new char[20];
	 char dummySpace = ' ';
	 cursor = root = NULL;
	 ifstream fin;

	 // set file name
	 char fileName[] = "input1.txt";

	 // get data
	 fin.open( fileName );
	 fin >> usrnm >> dummySpace >> pswd;

	 //contiue to get data until at the end of file
	 while( fin.good() )
	 {
	  addItem(usrnm, pswd);
	  fin >> usrnm >> dummySpace >> pswd;
	 }

	 //close file
	 fin.close();
}
bool tree:: verifyUser( char *usrnm, char *pswd)
{
	 int val;
	 cursor = root;
	 bool found = false;

	 if( cursor != NULL )
	 found = find( usrnm, cursor );

	 if( found == true )
	 {
		  val = strcmp( cursor->password, pswd );
		  if( val == 0 )
		  {
		   cout << "Verified User" << endl;
		   delete[] usrnm;
		   delete[] pswd;
		   usrnm = pswd = NULL;
		   return true;
		  }

		  else 
		  {
			cout << "User Unverified" << endl;
			delete[] usrnm;
			delete[] pswd;
			usrnm = pswd = NULL;
			return false;
		  }
	 }
	 delete[] usrnm;
	 delete[] pswd;
	 usrnm = pswd = NULL;
	 return false;
}

tree:: ~tree()
{
	 // deallocate memory

	 Destroy(root);
	 root = NULL;
	 cursor = NULL;
}
