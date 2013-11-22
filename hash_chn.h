/* http://www.austincc.edu/comer/ds11f/program7.htm */

// Table class 

// Warning: The Table class does not have:
//     a destructor, 
//     copy constructor, 
//     or overloaded assignment operator.
// Do not depend on any of these working correctly.
// You should be able to do this assignment 
// without having to to write these functions.
// Just do not pass a Table by value, assign a Table to another Table, etc.

// Member functions

// CONSTRUCTOR function
//    Table( );
// Postcondition: The table is initialized as an empty table.
       
// MODIFICATION MEMBER FUNCTIONS
                  
// Insert function 
//    void insert( const RecordType& entry );
// Preconditions: entry.key >= 0. Also, if entry needs to be added to the table,
//    then there must be room left in the table (size( ) < TABLE_SIZE).
// Postcondition: If the table already has a record with key equal to 
//    the key in entry, that record will be replaced by entry.
//    Otherwise, entry will be added as a new record.

// CONSTANT MEMBER FUNCTIONS

// Find function
//     void find( int key, bool& found, RecordType& result ) const; 
// Preconditions:  key >= 0
// Postconditions: If a record with the indicated key is in the table, 
//    then found is true and result is set to a copy of that record.
//    Otherwise, found is false and result contains garbage. 
               
// Size function
//    int size( ) const; 
// Postcondition: The return value is the number if records in the table.


#include <cassert>
#include <cstdlib>
using namespace std;

//typedef int ItemType;
const int CAPACITY = 31;

template <typename ItemType>
struct RecordType
{
   int key;
   ItemType data;
};

template <typename ItemType>
struct Node
{
   RecordType<ItemType> rec;
   Node<ItemType>* next;
};

template <typename ItemType>
class Table
{
public:

   Table( )
   {
	   used = 0;
	   for ( int i = 0; i < CAPACITY; i++ )
		  table[i] = NULL;
	}

   void insert( const RecordType<ItemType>& entry )
   {
	   bool alreadyThere;
	   Node<ItemType>* nodePtr;

	   assert( entry.key >= 0 );

	   findPtr( entry.key, alreadyThere, nodePtr );
	   if( !alreadyThere )
	   {
		   int i = hash( entry.key );      // get index of "bucket" where entry belongs
		   // insert at beginning of list
		   Node<ItemType>* temp = new Node<ItemType>;
		   temp->rec = entry;      // copy record
		   temp->next = table[i];
		   table[i] = temp;
		   used++;
	   }
	   else 
	   {
		   // nodePtr points to existing record that should be updated
		   nodePtr->rec = entry;
	   } 
   }

   void find( int key, bool& found, RecordType<ItemType>& result ) const
   {
	   Node<ItemType>* nodePtr;
   
	   assert( key >= 0 );
   
	   findPtr( key, found, nodePtr );
	   if ( found )
	   {
		  result = nodePtr->rec;
	   }
   }

   inline int size( ) const {return used;}

private:
   void findPtr( int key, bool& found, Node<ItemType>*& nodePtr ) const
	{
	   int i;
	   Node<ItemType>* ptr;

	   i = hash( key );
	   ptr = table[i];
	   found = false;
	   while ( !found && ptr != NULL )
	   {
		  if ( key == ptr->rec.key )
		  {
			 found = true;
			 nodePtr = ptr;
		  }
		  ptr = ptr->next;
	   }   
	   if ( !found )
		  nodePtr = NULL;
	}

   inline int hash( int key ) const {return key % CAPACITY;}
   Node<ItemType>* table[CAPACITY];
   int used; 
};