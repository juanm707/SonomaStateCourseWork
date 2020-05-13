//////////////////////////////////////////////////////////////////
// Project: Project 4                                           //
// File: OrderedSet.hpp                                         //
// Author: Juan Martinez                                        //
// Class: CS215 Spring 2017                                     //
// Description: Header and implementation for Ordered Set class //
// includes Nodes, exception, and iteration.                    //
//////////////////////////////////////////////////////////////////

#ifndef ORDEREDSET_HPP
#define ORDEREDSET_HPP

#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class ST> class OrderedSet;
template <class ST> ostream & operator << (ostream & outs, const OrderedSet<ST> & L);

template <class ST>

class OrderedSet
{
   private:
      struct LNode
      {
         LNode ();
         ST data;
         LNode * next;
	 LNode * prev;
      };
  
   public:

  class Exception
  {
  public:
    Exception ();
    Exception (string msg);
    Exception (int idx);

    string Message () const;
  private:
    string message;
  };
  
  class Iterator
  {
  public:

    Iterator ();
    Iterator (LNode * NP);
    Iterator operator ++ ();
    ST & operator * () const;
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);
    bool operator == (const Iterator & other) const;
    bool operator != (const Iterator & other) const;
  private:
    LNode * current;
  };
  
      OrderedSet ();
      OrderedSet (const OrderedSet & other);
      ~OrderedSet ();
      OrderedSet & operator = (const OrderedSet & other);
      bool operator == (const OrderedSet & other);
      int Size () const;

  void SetDirection (dtype dir);
  dtype GetDirection () const;
  friend ostream & operator << <> (ostream & outs, const OrderedSet<ST> & L);
 
  void Forward (void function (const ST & param));
  void Backward (void function (const ST & param));

  void PrintValue (const int & value);

  Iterator begin () const;
  Iterator rbegin () const;
  Iterator end () const;
  Iterator rend () const;

  ST & operator [] (const int & index) const;

  void Clear ();
  bool IsEmpty () const;
  bool IsIn (const ST & value) const;
  bool Insert (const ST & value);
  bool Delete (const ST & value);
  OrderedSet operator + (const OrderedSet & other);
  OrderedSet operator * (const OrderedSet & other);
  
   private:
  
      bool InsertFirst (const ST & value);
      bool InsertLast (const ST & value);
      bool DeleteFirst ();
      bool DeleteLast ();
  
      LNode * first;
      LNode * last;
      int size;
      dtype direction;
      
};

//////////////////////////////////////////////////////////////////
// Function: LNode ()                                           //
// Parameters: none                                             //
// Return value: none                                           //
// Description: Default constructor for the Node class. This    //
// function will initialize the next and prev pointers of the   //
// Node class to NULL. The data value initialization is left to //
// the data type class. Data values of primitive types may, or  //
// may not, be initialized (compiler dependent). Sample file    //
// for testing OrderedSet and WordData                          //
//////////////////////////////////////////////////////////////////

template <class ST>
OrderedSet<ST>::LNode::LNode ()
{ 
  next = NULL;
  prev = NULL;
}

//////////////////////////////////////////////////////////////////
// Function: OrderedSet ()                                      //
// Parameters: none                                             //
// Return value: none                                           //
// Description: Default constructor for the OrderedSet class.   //
// function will initialize first and last pointers to null,    //
// set size of set to 0, and make direction of set to forward   //
//////////////////////////////////////////////////////////////////

template <class ST>
OrderedSet<ST>::OrderedSet ()
{ 
  first = NULL;
  last = NULL;
  size = 0;
  direction = FORWARD;
}

//////////////////////////////////////////////////////////////////
// Function: OrderedSet (const OrderedSet & other)              //
// Parameters: "other" which is another OrderedSet.             //
// Return value: none                                           //
// Description: This function is the copy constructor and sets  //
// value of size to 0, first to NULL and copies data of a list  //
// into another list.                                           //
//////////////////////////////////////////////////////////////////

template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
{ 
  size = 0;
  first = NULL;
  
  for (LNode * n = other.first; n != NULL; n = n->next)
    {
      InsertLast (n->data);
    }
  direction = other.direction;
  
}

//////////////////////////////////////////////////////////////////
// Function: ~OrderedSet ()                                     //
// Parameters: none                                             //
// Return value: none                                           //
// Description: This function will delete the first item in     //
// the list                                                     //
//////////////////////////////////////////////////////////////////        

template <class ST>
OrderedSet<ST>::~OrderedSet ()
{ 
  while (first)
    {
      DeleteFirst();
    }
}

//////////////////////////////////////////////////////////////////
// Function: operator = (const OrderedSet & other)              //
// Parameters: "other" which is another OrderedSet.             //
// Return value: this - an OrderedSet                           //
// Description: This function will check for self assignment    //
//////////////////////////////////////////////////////////////////        

template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet<ST> & other)
{
  if (this == &other)
    {
      return * this;
    }

  while (first)
    {
      DeleteFirst();
    }
  for (LNode* n = other.first; n != NULL; n = n->next)
    {
      InsertLast(n->data);
    }
  direction = other.direction;
  return * this;
}

//////////////////////////////////////////////////////////////////
// Function: operator == (const OrderedSet & other)             //
// Parameters: "other" which is another OrderedSet.             //
// Return value: bool                                           //
// Description: This function wil check for equality between    //
// two lists.                                                   //
//////////////////////////////////////////////////////////////////        

template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet & other)
{ 
  if (size != other.size)
    {
      return false;
    }
  
  int i = 0;

  LNode* np = first;
  LNode* op = other.first;
  
  while (i < size)
    {
      if (np->data != op->data)
	{
	  return false;
	}

      np = np->next;
      op = op->next;

      i++;
    }

  return true;
  
}

//////////////////////////////////////////////////////////////////
// Function: Size ()                                            //
// Parameters: none                                             //
// Return value: int - size of set                              //
// Description: This function will return the value of size.    //
//////////////////////////////////////////////////////////////////        

template <class ST>
int OrderedSet<ST>::Size () const
{ 
  return size;
}

//////////////////////////////////////////////////////////////////
// Function: SetDirection (dtype dir)                           //
// Parameters: "dir" - a direction type                         //
// Return value: none                                           //
// Description: This function will set the direction of the set //
// to the dtype that is passed.                                 //
//////////////////////////////////////////////////////////////////        

template <class ST>
void OrderedSet<ST>::SetDirection (dtype dir)
{
  direction = dir;
}

//////////////////////////////////////////////////////////////////
// Function: GetDirection ()                                    //
// Parameters: none                                             //
// Return value: dtype - the direction of the set               //
// Description: This function will return the value of          //
// direction of the set.                                        //
//////////////////////////////////////////////////////////////////        

template <class ST>
dtype OrderedSet<ST>::GetDirection () const
{
  return direction;
}

//////////////////////////////////////////////////////////////////
// Function: operator << (ostream & outs, const OrderedSet & L) //
// Parameters: Outs - Output stream and L - ordered set         //
// Return value: ostream                                        //
// Description: This function will traverse the list, output    //
// the data values, and return outs.                            //
//////////////////////////////////////////////////////////////////        

template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & L)
{ 
  if (L.first == NULL)
    {
    cout << "{}";
    return outs;
    }
    
  if (L.direction == FORWARD)
    {//Print the list from beginning (first) to end
      outs << '{' << L.first->data;

      typename OrderedSet<ST>::LNode* n;
      for (n = L.first->next; n != NULL; n = n->next)
	outs << ',' << n->data;
      outs << '}';
    }
  
  else //L.direction == BACKWARD
    {//Print the list from end to beginning
      outs << '{' << L.last->data;

      typename OrderedSet<ST>::LNode* n;
      for (n = L.last->prev; n != NULL; n = n->prev)
	outs << ',' << n->data;
      outs << '}';
    }

  return outs;
  
}

//////////////////////////////////////////////////////////////////
// Function: InsertFirst (const ST & value)                     //
// Parameters: a value for data.                                //
// Return value: bool                                           //
// Description: This function will allocate space for a new     //
// node. False if space cannot be allocated. Set data of the    //
// new node to the input value, set the next of the new node to //
// the current first. Set the first of the list to the new node.//
// Increment the size of the list, and return true.             //
//////////////////////////////////////////////////////////////////        

template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
{
  LNode* nw = new LNode;

  if (nw == NULL)
    {
      return false;
    }

  if (size == 0)
    {
      nw->data = value;
      nw->next = NULL;
      nw->prev = NULL;
      first = nw;
      last = nw;
      size++;
      return true;
    }
  if (size >= 1)
    {
      nw->data = value;
      nw->next = first;
      nw->prev = NULL;
      first->prev = nw;
      
      first = nw;
      size++;
      return true;
    }
  
}

//////////////////////////////////////////////////////////////////
// Function: InsertLast (const ST & value)                      //
// Parameters: a value for data.                                //
// Return value: bool                                           //
// Description: This function will allocate space for a new     //
// node. False if space cannot be allocated. Set data of the    //
// new node to the input value. Set last of set to this new node//
// and increment the size of the list, and return true.         //
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::InsertLast (const ST & value)
{ 
  if (size == 0)
    {
      return InsertFirst(value);
    }
  
  LNode* nw = new LNode;
  
  if (nw == NULL)
    {
      return false;
    }

  if (size == 1)
    {
      nw->data = value;
      nw->next = NULL;
      nw->prev = last;
  
      last->next = nw;
      last = nw;
      size++;
      return true;
    }
  
  nw->data = value;
  nw->next = NULL;
  nw->prev = last;
  
  last->next = nw;
  last = nw;
  size++;
  
  return true;
  
}

//////////////////////////////////////////////////////////////////
// Function: DeleteFirst ()                                     //
// Parameters: none.                                            //
// Return value: bool                                           //
// Description: This function will delete the first value       //
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
{ 
  if (size == 0)
    {
      return false;
    }

  
  if (size == 1)
    {
      LNode* temp = first;
      first = NULL;
      last = NULL;
      delete temp;
      size--;
      return true;
    }

  LNode* temp = first;
  first = first->next;
  first->prev = NULL;
  
  delete temp;
  size--;
  
  
  return true;
  
}

//////////////////////////////////////////////////////////////////
// Function: DeleteLast ()                                      //
// Parameters: none.                                            //
// Return value: bool                                           //
// Description: This function will delete the last value if     //
// present.                                                     //
//////////////////////////////////////////////////////////////////           

template <class ST>
bool OrderedSet<ST>::DeleteLast ()
{ 
  if (size == 0)
    {
      return false;
    }

  if (size == 1)
    {
      return DeleteFirst();
    }

  LNode* temp = last;
  
  last = last->prev;
  last->next = NULL;
  temp->prev = NULL;
  
  delete temp;
  size--;
  return true;
  
}

//////////////////////////////////////////////////////////////////
// Function: Forward ()                                         //
// Parameters: a function, and data for that function           //
// Return value: none                                           //
// Description: This function will pass the value of data of    //
// each node to a function                                      //
//////////////////////////////////////////////////////////////////           

template <class ST>
void OrderedSet<ST>::Forward (void function (const ST & param))
{
  for (LNode* n = first; n; n = n->next)
    function (n->data);

}

//////////////////////////////////////////////////////////////////
// Function: Backward ()                                        //
// Parameters: a function, and data for that function           //
// Return value: none                                           //
// Description: This function will pass the value of data of    //
// each node to a function but starting backwards/from end.     //
//////////////////////////////////////////////////////////////////   

template <class ST>
void OrderedSet<ST>::Backward (void function (const ST & param))
{
  for (LNode * n = last; n; n = n->prev)
    function (n->data);
}

//////////////////////////////////////////////////////////////////
// Function: PrintValue (const int & value)                     //
// Parameters: an int value                                     //
// Return value: none                                           //
// Description: This function will output the value passed.     //      
//////////////////////////////////////////////////////////////////   

void PrintValue (const int & value)
{
  cout << "The value in the list is " << value << endl;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator ()                                        //
// Parameters: none                                             //
// Return value: none                                           //
// Description: Sets the current variable = NULL.               //
////////////////////////////////////////////////////////////////// 

template <class ST>
OrderedSet<ST>::Iterator::Iterator ()
{
  current = NULL;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator (LNode * NP)                              //
// Parameters: an LNode NP                                      //
// Return value: none                                           //
// Description: This function sets current = to the Node passed.//
////////////////////////////////////////////////////////////////// 

template <class ST>
OrderedSet<ST>::Iterator::Iterator (LNode * NP)
{
  current = NP;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator ++ ()                           //
// Parameters: none                                             //
// Return value: *typename                                      //
// Description: This function will incremenet current if possible/
////////////////////////////////////////////////////////////////// 

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ ()
{
  if (current == NULL)
    throw(Exception("Cannot incremenet a NULL iterator"));
	  
  current = current->next;
  return *this;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator ++ (int)                        //
// Parameters: int                                              //
// Return value: *typename                                      //
// Description: This function will pre-incremenet current if    //
// possible.                                                    //
//////////////////////////////////////////////////////////////////              

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ (int)
{
  Iterator temp = *this;
  if (current == NULL)
    throw(Exception("Cannot increment a NULL iterator"));
  
  current = current->next;
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator -- ()                           //
// Parameters: none                                             //
// Return value: *typename                                      //
// Description: This function will decrement current if possible//
//////////////////////////////////////////////////////////////////              

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- ()
{
  if (current == NULL)
    throw(Exception("Cannot decrement a NULL iterator"));
  
  current = current->prev;
  return *this;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator -- (int)                        //
// Parameters: none                                             //
// Return value: *typename                                      //
// Description: This function will pre-decrement current if     //
// possible.                                                    //
//////////////////////////////////////////////////////////////////     

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- (int)
{
  Iterator temp = *this;
  if (current == NULL)
    throw(Exception("Cannot decrement a NULL iterator"));
	  
  current = current->prev;
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator == (const Iterator & other) const/
// Parameters: other - an Iterator object                       //
// Return value: bool                                           //
// Description: This function will return wether two Iterators  //
// are equal or not.                                            //
//////////////////////////////////////////////////////////////////     

template <class ST>
bool OrderedSet<ST>::Iterator::operator == (const Iterator & other) const
{
  return current == other.current;
}

//////////////////////////////////////////////////////////////////
// Function: Iterator::operator != (const Iterator & other) const/
// Parameters: other - an Iterator object                       //
// Return value: bool                                           //
// Description: This function will return wether two Iterators  //
// are equal or not.                                            //
////////////////////////////////////////////////////////////////// 

template <class ST>
bool OrderedSet<ST>::Iterator::operator != (const Iterator & other) const
{
  return current != other.current;
}

//////////////////////////////////////////////////////////////////
// Function: begin () const                                     //
// Parameters: none                                             //
// Return value: typename                                       //
// Description: This function will make an Iterator start at    //
// beginning of a set.                                          //
////////////////////////////////////////////////////////////////// 

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin () const
{
  Iterator temp (first);
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: rbegin () const                                    //
// Parameters: none                                             //
// Return value: typename                                       //
// Description: This function will make an Iterator start at    //
// end of a set.                                                //
//////////////////////////////////////////////////////////////////  

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin () const
{
  Iterator temp (last);
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: end () const                                       //
// Parameters: none                                             //
// Return value: typename                                       //
// Description: This function will make an Iterator start at    //
// very end of a set.                                           //
//////////////////////////////////////////////////////////////////  

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end () const
{
  Iterator temp;
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: rend () const                                      //
// Parameters: none                                             //
// Return value: typename                                       //
// Description: This function will make an Iterator start at    //
// end of a set.                                                //
//////////////////////////////////////////////////////////////////  

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend () const
{
  Iterator temp;
  return temp;
}

//////////////////////////////////////////////////////////////////
// Function: operator [] (const int & index) const              //
// Parameters: int index                                        //
// Return value: ST                                             //
// Description: This function will return the data at an        //
// appropriate index of a set.                                  //
//////////////////////////////////////////////////////////////////  

template <class ST>
ST & OrderedSet<ST>::operator [] (const int & index) const
{
  if (index < 0)
    throw(Exception(index));
  if (index >= size)
    throw(Exception(index));
  
  OrderedSet<ST>::LNode * n = first;

  for (int i = 0; i < index; i++)
    {
      n = n->next;
    }
  
  return n->data;
}

//////////////////////////////////////////////////////////////////
// Function: operator * () const                                //
// Parameters: none                                             //
// Return value: ST                                             //
// Description: This function will make return data of a specific/
// pointer.                                                     //
//////////////////////////////////////////////////////////////////  

template <class ST>
ST & OrderedSet<ST>::Iterator::operator * () const
{
      if (current == NULL)
	{
	  throw(Exception("Cannot dereference a NULL pointer"));
	}
      return current->data;
  
}

//////////////////////////////////////////////////////////////////
// Function: Clear ()                                           //
// Parameters: none                                             //
// Return value: none                                           //
// Description: This function will clear a set / delete all items/
//////////////////////////////////////////////////////////////////  

template <class ST>
void OrderedSet<ST>::Clear ()
{ 
  while (0 < size)
    {
      DeleteFirst();
    }
}

//////////////////////////////////////////////////////////////////
// Function: IsEmpty () const                                   //
// Parameters: none                                             //
// Return value: bool                                           //
// Description: This function will check if a set's size is 0.  //
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::IsEmpty () const
{
  if (size == 0)
    {
      return true;
    }

  return false;
}

//////////////////////////////////////////////////////////////////
// Function: IsIn (const ST & value) const                      //
// Parameters: ST value                                         //
// Return value: bool                                           //
// Description: This function will check if a specific value is //
// in the set or not.                                           //
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::IsIn (const ST & value) const
{
  LNode * nn = new LNode;
  if (nn == NULL)
    {
      return false;
    }
  nn->data = value;

  LNode * nx = first;

  while (nx != NULL)
    {
      if (nx->data == nn->data)
	{
	 return true;
	}
      nx = nx->next;
    }
  
  return false; 
}

//////////////////////////////////////////////////////////////////
// Function: Insert (const ST & value) const                    //
// Parameters: ST Value                                         //
// Return value: bool                                           //
// Description: This function will insert a value into the set at/
// that the appropriate place. False if already in or no new space
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::Insert (const ST & value)
{
  
  if (size == 0)
    {
      return InsertFirst(value);
    }

  if (value < first->data)
    {
      return InsertFirst(value);
    }

  if (value > last->data)
    {
      return InsertLast(value);
    }
  

  if (IsIn(value))
    {
      return false;
    }

  LNode * nn = new LNode;
  if (nn == NULL)
    return false;
  nn->data = value;
  
  //Traverse the list
  LNode * nx = first;
  while (nx->data < value)
    {
      nx = nx->next;
    }

  LNode * pv = nx->prev;
  nn->prev = pv;
  nx->prev = nn;
  pv->next = nn;
  nn->next = nx;
  size++;
  return true;
  
}

//////////////////////////////////////////////////////////////////
// Function: Delete (const ST & value) const                    //
// Parameters: ST value                                         //
// Return value: bool                                           //
// Description: This function will delete a specific value      //
// only if it is in the set.                                    //
//////////////////////////////////////////////////////////////////  

template <class ST>
bool OrderedSet<ST>::Delete (const ST & value)
{
  if (size == 0)
    {
      return false;
    }

  if (size == 1)
    {
      return DeleteFirst();
    }

  if (first->data == value)
    {
      return DeleteFirst();
    }

  if (last->data == value)
    {
      return DeleteLast();
    }
  
  if (IsIn(value))
    {
      LNode * dl = new LNode;
      if (dl == NULL)
	{
	  return false;
	}

      dl->data = value;
      LNode * nx = first;
      while(nx->data != value)
	{
	  nx = nx->next;
	}
      LNode * pv = nx->prev;
      LNode * nextnext = nx->next;
      
      pv->next = nextnext;
      nextnext->prev = pv;
      size--;
      delete nx;
      return true;
    }

  return false;
      
}

//////////////////////////////////////////////////////////////////
// Function: operator + (const OrderedSet & other)              //
// Parameters: other - an OrderedSet of same ST type            //
// Return value: OrderedSet<ST>                                 //
// Description: This function will return a new set of all      //
// values in two sets.                                          //
//////////////////////////////////////////////////////////////////         

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator + (const OrderedSet & other)
{
  OrderedSet<ST> unionset;

  LNode * nd = first;
  LNode * of = other.first;

  while (nd != NULL || of != NULL)
    {
      if (nd!= NULL)
	{
      unionset.Insert(nd->data);
      nd = nd->next;
	}
      if (of != NULL)
	{
      unionset.Insert(of->data);
      of = of->next;
	}
    }
  return unionset;
  
  
}

//////////////////////////////////////////////////////////////////
// Function: operator * (const OrderedSet & other)              //
// Parameters: other - an OrderedSet of same ST type            //
// Return value: OrderedSet<ST>                                 //
// Description: This function will return a new set of all the  //
// values that are in both sets.                                //
////////////////////////////////////////////////////////////////// 

template <class ST>
OrderedSet<ST> OrderedSet<ST>::operator * (const OrderedSet & other)
{
  OrderedSet<ST> interset;

  LNode * o = other.first;

  while (o != NULL)
    {
      if (IsIn(o->data))
	{
	  interset.Insert(o->data);
	}
      o = o->next;
    }
  return interset;
}

//////////////////////////////////////////////////////////////////
// Function: Exception::Exception ()                            //
// Parameters: none                                             //
// Return value: none                                           //
// Description: N/A                                             //
////////////////////////////////////////////////////////////////// 

template <class ST>
OrderedSet<ST>::Exception::Exception ()
{
}

//////////////////////////////////////////////////////////////////
// Function: Exception::Exception (string msg)                  //
// Parameters: a string msg                                     //
// Return value: none                                           //
// Description: Stores a string message in variable message.    //
//////////////////////////////////////////////////////////////////

template <class ST>
OrderedSet<ST>::Exception::Exception (string msg)
{
  message = msg;
}

//////////////////////////////////////////////////////////////////
// Function: Exception::Exception (int idx)                     //
// Parameters: int - idx which is index not in bounds.          //
// Return value: none                                           //
// Description:                                                 //
//////////////////////////////////////////////////////////////////      

template <class ST>
OrderedSet<ST>::Exception::Exception (int idx)
{
  stringstream ss (stringstream::in | stringstream::out);
  ss << "Subscript [" << idx << "] out of range";
  getline(ss, message);
}

//////////////////////////////////////////////////////////////////
// Function: Exception::Message () const                        //
// Parameters: none                                             //
// Return value: string                                         //
// Description: Returns string message variable value.          //
//////////////////////////////////////////////////////////////////      

template <class ST>
string OrderedSet<ST>::Exception::Message() const
{
  return message;
}

#endif

